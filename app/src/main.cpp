#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/display/mb_display.h>

#define SLEEP_TIME_MS 1000
#define LED_NODE DT_ALIAS(app_led)

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

static const struct mb_image pixel_on = MB_IMAGE(
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 });

static const struct mb_image pixel_off = MB_IMAGE(
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 });

int main(void)
{
#if DT_NODE_HAS_STATUS(LED_NODE, okay)
    LOG_INF("LED alias app-led present");
#else
    LOG_INF("LED alias app-led NOT present");
#endif
    struct mb_display *disp = mb_display_get();
    bool led_state = true;

    while (1) {
        const struct mb_image *img = led_state ? &pixel_on : &pixel_off;
        mb_display_image(disp, MB_DISPLAY_MODE_SINGLE, SYS_FOREVER_MS, img, 1);
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        led_state = !led_state;
        k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
    }
    return 0;
}
