# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
SLEEP_LED_ENABLE = yes
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output

AUDIO_SUPPORTED = no        # Audio is not supported

RGBLIGHT_SUPPORTED = yes    # RGB underglow is supported, but not enabled by default
RGBLIGHT_ENABLE = yes     # Enable keyboard RGB matrix functionality
SPLIT_KEYBOARD = yes
NO_USB_STARTUP_CHECK = yes
SERIAL_DRIVER = vendor
RGBLIGHT_DRIVER = ws2812
WS2812_DI_PIN = GP0
USB_VBUS_PIN = GP1
