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

This firmware includes fixes for wireless split keyboard operation. By default, **deep sleep (LPWR) is disabled in wireless mode** to ensure both keyboard halves can wake the keyboard.

### Current Behavior (Default)

- ✅ **Both left and right halves can wake the keyboard**
- ✅ RGB turns off after 2 minutes (`RGB_MATRIX_TIMEOUT`)
- ✅ Keyboard enters light sleep mode (PRESLEEP/suspend)
- ✅ Split communication remains active
- ⚠️ **Battery life**: Weeks to a month of standby (depending on usage)

### Re-enabling Deep Sleep (LPWR Mode)

If you prefer **maximum battery life** (potentially months of standby) and don't mind that **only the left half can wake the keyboard**, you can re-enable deep sleep:

**In `keyboards/epomaker/split65/split65.c`, change:**

```c
bool lpwr_is_allow_timeout_hook(void) {
    // Don't allow LPWR deep sleep in wireless mode at all
    // When master enters LPWR, it stops polling the slave entirely
    // This means right-side keys can never wake the keyboard
    // Both halves must stay awake enough to maintain split communication
    if (wireless_get_current_devs() == DEVS_USB) {
        return false;
    }

    // Prevent deep sleep when wireless - use lighter sleep modes only
    return false;
}
```

**To:**

```c
bool lpwr_is_allow_timeout_hook(void) {
    if (wireless_get_current_devs() == DEVS_USB) {
        return false;
    }

    return true;  // Allow deep sleep - only left half will wake keyboard
}
```

**Trade-offs with Deep Sleep Enabled:**

* ❌ **Right half CANNOT wake the keyboard** - only left-side keys work after sleep
* ❌ Must press a key on the LEFT half to wake, then right side works
* ✅ **Maximum battery life** - months of standby time
* ✅ Deep LPWR mode stops almost all power consumption

**Why this limitation exists:**

In deep sleep (LPWR), the master (left) half completely stops polling the slave (right) half to save power. When the master is in LPWR:

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
