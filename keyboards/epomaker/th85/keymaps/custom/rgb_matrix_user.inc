// !!! DO NOT ADD #pragma once !!!

RGB_MATRIX_EFFECT(IDLE_RIPPLE)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
 * ============================================================
 * TH85 IDLE RIPPLE
 * ============================================================
 *
 * Two simultaneous concentric waves.
 *
 * Keyboard coordinates:
 *   X ≈ 0..224
 *   Y ≈ 10..60
 *
 * Center:
 *   X = 112
 *   Y = 40
 *
 * LEDs 0..83:
 *   Keyboard keys
 *
 * LEDs 84..91:
 *   Logo
 *
 * LEDs 92..129:
 *   Side strip
 */


/* ------------------------------------------------------------
 * Ripple geometry
 * ------------------------------------------------------------ */

#define TH85_RIPPLE_CENTER_X       112
#define TH85_RIPPLE_CENTER_Y        40

#define TH85_RIPPLE_MAX_RADIUS     120

/*
 * Half the cycle, giving two equally spaced waves.
 */
#define TH85_RIPPLE_SEPARATION      60


/* ------------------------------------------------------------
 * Animation
 * ------------------------------------------------------------ */

#define TH85_RIPPLE_FRAME_MS        25
#define TH85_RIPPLE_STEP              3
#define TH85_RIPPLE_WIDTH            10


/* ------------------------------------------------------------
 * Shared state
 *
 * These variables are defined in keymap.c.
 * ------------------------------------------------------------ */

extern uint16_t th85_ripple_radius;
extern uint32_t th85_ripple_timer;


/* ------------------------------------------------------------
 * Distance
 * ------------------------------------------------------------ */

static uint16_t th85_ripple_distance(uint8_t led_index) {

    int16_t dx =
        (int16_t)g_led_config.point[led_index].x -
        TH85_RIPPLE_CENTER_X;

    int16_t dy =
        (int16_t)g_led_config.point[led_index].y -
        TH85_RIPPLE_CENTER_Y;

    uint16_t distance_squared =
        (uint16_t)(
            (dx * dx) +
            (dy * dy)
        );

    return sqrt16(distance_squared);
}


/* ------------------------------------------------------------
 * Ring brightness
 * ------------------------------------------------------------ */

static uint8_t th85_ring_brightness(
    uint16_t distance,
    uint16_t radius
) {

    int16_t difference =
        (int16_t)distance -
        (int16_t)radius;

    if (difference < 0) {
        difference = -difference;
    }

    if (difference >= TH85_RIPPLE_WIDTH) {
        return 0;
    }

    return (
        uint8_t
    )(
        255 -
        (
            ((uint16_t)difference * 255) /
            TH85_RIPPLE_WIDTH
        )
    );
}


/* ------------------------------------------------------------
 * Ripple effect
 * ------------------------------------------------------------ */

static bool IDLE_RIPPLE(effect_params_t *params) {

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    /*
     * When the effect starts, begin the wave at the center.
     */
    if (params->init) {
        th85_ripple_radius = 0;
        th85_ripple_timer = g_rgb_timer;
    }


    /*
     * Advance both waves together.
     */
    if (
        timer_elapsed32(th85_ripple_timer) >=
        TH85_RIPPLE_FRAME_MS
    ) {

        th85_ripple_timer = g_rgb_timer;

        th85_ripple_radius +=
            TH85_RIPPLE_STEP;

        /*
         * Start a new cycle once the first wave reaches
         * the outer edge.
         */
        if (
            th85_ripple_radius >
            TH85_RIPPLE_MAX_RADIUS
        ) {

            th85_ripple_radius = 0;
        }
    }


    hsv_t hsv =
        rgb_matrix_get_hsv();


    /*
     * --------------------------------------------------------
     * KEYBOARD LEDs
     * --------------------------------------------------------
     *
     * Only LEDs 0..83 belong to the key matrix.
     */
    for (
        uint8_t i = led_min;
        i < led_max && i < 84;
        i++
    ) {

        uint16_t distance =
            th85_ripple_distance(i);


        /*
         * First wave.
         */
        uint8_t brightness_1 =
            th85_ring_brightness(
                distance,
                th85_ripple_radius
            );


        /*
         * Second wave.
         */
        uint16_t second_radius =
            th85_ripple_radius +
            TH85_RIPPLE_SEPARATION;


        if (
            second_radius >
            TH85_RIPPLE_MAX_RADIUS
        ) {

            second_radius -=
                TH85_RIPPLE_MAX_RADIUS;
        }


        uint8_t brightness_2 =
            th85_ring_brightness(
                distance,
                second_radius
            );


        /*
         * Use whichever wave is brighter.
         */
        uint8_t brightness =
            brightness_1 > brightness_2
                ? brightness_1
                : brightness_2;


        if (brightness == 0) {

            rgb_matrix_set_color(
                i,
                0,
                0,
                0
            );

            continue;
        }


        hsv_t ring_hsv = hsv;

        ring_hsv.v =
            (
                (uint16_t)hsv.v *
                brightness
            ) / 255;


        rgb_t rgb =
            hsv_to_rgb(ring_hsv);


        rgb_matrix_set_color(
            i,
            rgb.r,
            rgb.g,
            rgb.b
        );
    }

    return false;
}

#endif