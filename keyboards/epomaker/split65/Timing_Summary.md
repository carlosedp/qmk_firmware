⏱️ Epomaker Split65 Sleep & Timing Summary

🎨 RGB LEDs
    • RGB turns off after: 2 minutes (120,000 ms)
    • `RGB_MATRIX_TIMEOUT = 120000`
    • LEDs fade out to save power

😴 Sleep Stages

Stage 1: Light Sleep (Wireless Connected)
    • Triggers after: 5 minutes (300,000 ms)
    • `HS_SLEEP_TIMEOUT = 300000`
    • What happens:
        - Keyboard enters light sleep
        - Still connected to Bluetooth/2.4G
        - Can wake quickly with any keypress
        - Split communication stays active

Stage 2: Deep Sleep (USB Mode Only)
    • Triggers after: 10 minutes (600,000 ms)
    • `LPWR_TIMEOUT = 600000`
    • What happens:
        - Keyboard enters deeper sleep
        - USB disconnects (if in USB mode)
        - Takes longer to wake up (1 second delay)
        - Split may need to re-sync

📡 Bluetooth/2.4G Module Deep Sleep
    • Triggers after: 30 minutes (1,800,000 ms)
    • Configured via `MD_SND_CMD_DEVCTRL_SLEEP_BT_EN`
    • What happens:
        - Wireless module fully disconnects
        - Maximum battery savings
        - First keypress reconnects (may take 2-5 seconds)

🔌 USB Suspend Behavior
    • USB suspend detection: 7 seconds (7,000 ms)
    • `USB_POWER_DOWN_DELAY = 7000`
    • What happens:
        - Waits 7 seconds after computer sleeps
        - Then triggers keyboard sleep
        - Prevents accidental wake-ups

⚡ Wake-up Delays
    • USB wake delay: 1 second (1,000 ms)
    • `suspend_wakeup_delay = 1000`
    • Split sync delay: 50 ms (added in our fix)
    • Prevents RGB flickering
    • Ensures both halves wake together
