# EPOMAKER Split65

* Keyboard Maintainer: [EPOMAKER](https://github.com/Epomaker)
* Hardware Supported: EPOMAKER Split65
* Hardware Availability: EPOMAKER Split65

Clone this repo:

    git clone https://github.com/carlosedp/qmk_firmware.git

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb epomaker/split65 -km via

Flashing example for this keyboard:

    qmk flash -kb epomaker/split65 -km via

Or use QMK Toolbox.


## Flashing Instructions

To reset **both sides** of the keyboard into bootloader mode, do the following:

**Left Side:**

* Hold the Escape key while connecting the USB cable (it might erase persistent settings)
* Flash the firmware using QMK Toolbox or command line when DFU mode is detected.

**Right Side:**

* Move the switch behind of the RShift key (you should remove the keycap) to the lower position.
* Remove both the Space keycap and switch. Insert a tweezer or paper clip shorting the two holes beside the central switch hole while connecting the USB cable to the right half. The DFU pads are behind the switch position.
* After flashing this firmware, you can do this by holding the "7" key while plugging the USB cable instead of shorting the holes. Changing the switch to the down position is still required.
* **NOTE**: Don't forget making switch back up! It won't work unless the switch is in the up position.
  ![Howto](https://github.com/gwangyi/Split65/raw/main/howto.jpg)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Power Management & Battery Life

This firmware is configured for **maximum battery life** in wireless mode using deep sleep (LPWR). By default, **only the left half can wake the keyboard** from deep sleep.

### Current Behavior (Default - Deep Sleep Enabled)

- ⚠️ **Only the left half can wake the keyboard** from deep sleep
- ✅ **Maximum battery life**: Months of standby time
- ✅ RGB turns off after 2 minutes (`RGB_MATRIX_TIMEOUT`)
- ✅ Keyboard enters deep sleep (LPWR) after 10 minutes (`LPWR_TIMEOUT`)
- ✅ Bluetooth module disconnects after 30 minutes of inactivity
- ✅ Minimal power consumption in deep sleep mode

**Important Notes:**
- After waking from deep sleep, both halves work normally. You just need to press a left-side key first to wake the keyboard.
- **The Bluetooth connection typically stays active** even after the MCU enters deep sleep. This is normal - the wireless module firmware handles BT independently.
- Battery savings come from the MCU being in LPWR deep sleep, not from BT disconnecting.
- **To verify deep sleep is working:** After 10 minutes, press a **right-side key** - if it doesn't wake the keyboard, deep sleep is active ✅. Then press a left-side key to wake.

### Enabling Both-Halves Wake (Reduced Battery Life)

If you need **both left and right halves to wake the keyboard** and don't mind shorter battery life (weeks to a month), you can disable deep sleep:

**In `keyboards/epomaker/split65/split65.c`, find:**

```c
bool lpwr_is_allow_timeout_hook(void) {
    // Enable LPWR deep sleep in wireless mode for maximum battery life
    // Trade-off: Only the left half can wake the keyboard from deep sleep
    // 
    // When master enters LPWR, it stops polling the slave to save power
    // This means right-side keys cannot wake the keyboard
    //
    // To allow both halves to wake (at cost of battery life):
    // Change the return value below from true to false
    
    // In USB mode, don't use LPWR - USB host handles power management
    if (wireless_get_current_devs() == DEVS_USB) {
        return false;
    }

    // Enable deep sleep in wireless mode - left-side wake only
    // Change to 'return false;' for both-halves wake with reduced battery life
    return true;
}
```

**Change the last line to:**

```c
    return false;  // Disable deep sleep - both halves can wake keyboard
}
```

**Benefits with Deep Sleep Disabled:**

* ✅ **Both left and right halves can wake the keyboard**
* ✅ Split communication remains active during sleep
* ⚠️ **Battery life**: Weeks to a month of standby (reduced compared to deep sleep)
* ⚠️ Higher idle power consumption

**Why this limitation exists:**

In deep sleep (LPWR), the master (left) half completely stops polling the slave (right) half to save maximum power. When the master is in LPWR:

* Split UART communication is suspended
* The master cannot detect keypresses from the slave
* Only the master's own matrix pins can trigger a wake interrupt

This is a fundamental hardware limitation of wireless split keyboards - you cannot have both deep sleep on the master AND the ability for the slave to wake it.

### Sleep Timeouts

You can adjust sleep timeouts in `keyboards/epomaker/split65/keymaps/via/config.h`:

```c
#define RGB_MATRIX_TIMEOUT 120000   // RGB off after 2 minutes
#define HS_SLEEP_TIMEOUT 300000     // Light sleep after 5 minutes  
#define LPWR_TIMEOUT 600000         // Deep sleep after 10 minutes (if enabled)
```
