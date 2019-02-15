#include QMK_KEYBOARD_H

enum alt_keycodes {
    L_BRI = SAFE_RANGE, //LED Brightness Increase
    L_BRD,              //LED Brightness Decrease
    L_PTN,              //LED Pattern Select Next
    L_PTP,              //LED Pattern Select Previous
    L_PSI,              //LED Pattern Speed Increase
    L_PSD,              //LED Pattern Speed Decrease
    L_ORI,              //LED Pattern orientation
    L_GLITI,            //LED Breath Speed Increase
    L_GLITD,            //LED Breath Speed Decrease
    L_GLITSM,           //LED Glitter smooth (glitter vs clouds)
    L_T_ONF,            //LED Toggle On / Off
    L_ON,               //LED On
    L_OFF,              //LED Off
    L_T_GCM,            //LED Toggle Game Color Mode
    L_T_BR,             //LED Toggle Breath Effect
    L_T_GLIT,           //LED Toggle Glitter Effect
    L_T_PTD,            //LED Toggle Scrolling Pattern Direction
    U_T_AUTO,           //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,           //USB Toggle Automatic GCR control
    DBG_TOG,            //DEBUG Toggle On / Off
    DBG_MTRX,           //DEBUG Toggle Matrix Prints
    DBG_KBD,            //DEBUG Toggle Keyboard Prints
    DBG_MOU,            //DEBUG Toggle Mouse Prints
    MD_BOOT,            //Restart into bootloader after hold timeout
};

#define TG_NKRO MAGIC_TOGGLE_NKRO //Toggle 6KRO / NKRO mode

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_MUTE, \
        L_T_BR,  L_PSD,   L_BRI,   L_PSI,   L_GLITD,  L_GLITI,  KC_TRNS, U_T_AUTO,U_T_AGCR,KC_TRNS, KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_END, \
        L_T_GLIT,  L_PTP,   L_BRD,   L_PTN,   L_ORI,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MYCM, KC_CALC, KC_TRNS,          KC_F17, KC_VOLU, \
        L_GLITSM, L_T_GCM,  L_T_ONF, KC_TRNS, DEBUG,   MD_BOOT, TG_NKRO, KC_TRNS, KC_MPRV, KC_MNXT, KC_MPLY, KC_F18,           KC_F16, KC_VOLD, \
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_MPLY,                            KC_TRNS, KC_TRNS, KC_F13,  KC_F14, KC_F15  \
    ),
    /*
    [X] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, \
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  \
    ),
    */
};

const uint16_t PROGMEM fn_actions[] = {

};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (keyboard_report->mods & MOD_BIT(KC_LSHIFT) || keyboard_report->mods & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (keyboard_report->mods & MOD_BIT(KC_LCTL) || keyboard_report->mods & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (keyboard_report->mods & MOD_BIT(KC_LALT) || keyboard_report->mods & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case L_BRI:
            if (record->event.pressed) {
                if (LED_GCR_STEP > LED_GCR_MAX - gcr_desired) gcr_desired = LED_GCR_MAX;
                else gcr_desired += LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_BRD:
            if (record->event.pressed) {
                if (LED_GCR_STEP > gcr_desired) gcr_desired = 0;
                else gcr_desired -= LED_GCR_STEP;
                if (led_animation_breathing) gcr_breathe = gcr_desired;
            }
            return false;
        case L_ORI:
            if(record->event.pressed) {
              led_animation_orientation = !led_animation_orientation;
            }
            return false;
        case L_T_GCM:
            if (record->event.pressed) {
              led_game_colors = !led_game_colors;
            }
            return false;
        case L_GLITSM:
            if (record->event.pressed) {
              glitter_smooth = !glitter_smooth;
            }
            return false;
        case L_GLITI:
            if (record->event.pressed) {
                if(glitter_step < 16) {
                  glitter_step++;
                }
            }
            return false;
        case L_GLITD:
            if (record->event.pressed) {
                if(glitter_step > 1) {
                  glitter_step--;
                } else {
                  glitter_step = 1;
                }
            }
            return false;
        case L_PTN:
            if (record->event.pressed) {
                if (led_animation_id == led_setups_count - 1) led_animation_id = 0;
                else led_animation_id++;
            }
            return false;
        case L_PTP:
            if (record->event.pressed) {
                if (led_animation_id == 0) led_animation_id = led_setups_count - 1;
                else led_animation_id--;
            }
            return false;
        case L_PSI:
            if (record->event.pressed) {
                led_animation_speed += ANIMATION_SPEED_STEP;
            }
            return false;
        case L_PSD:
            if (record->event.pressed) {
                led_animation_speed -= ANIMATION_SPEED_STEP;
                if (led_animation_speed < 0) led_animation_speed = 0;
            }
            return false;
        case L_T_ONF:
            if (record->event.pressed) {
                led_enabled = !led_enabled;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_ON:
            if (record->event.pressed) {
                led_enabled = 1;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_OFF:
            if (record->event.pressed) {
                led_enabled = 0;
                I2C3733_Control_Set(led_enabled);
            }
            return false;
        case L_T_BR:
            if (record->event.pressed) {
                led_animation_breathing = !led_animation_breathing;
                if (led_animation_breathing) {
                    gcr_breathe = gcr_desired;
                    led_animation_breathe_cur = BREATHE_MIN_STEP;
                    breathe_dir = 1;
                }
            }
            return false;
        case L_T_GLIT:
            if (record->event.pressed) {
                led_animation_glittering = !led_animation_glittering;
                if (led_animation_glittering) {
                  uint8_t i;
                  for(i = 0; i < ISSI3733_LED_COUNT; i++) {
                    uint8_t rn = rand() % 255;
                    led_animation_glitter_cur[i] = rn;
                    if(i % 2) glitter_dir[i] = 1;
                    else glitter_dir[i] = -1;
                  }
                }
            }
            return false;
        case L_T_PTD:
            if (record->event.pressed) {
                led_animation_direction = !led_animation_direction;
            }
            return false;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}



led_instruction_t led_instructions[] = {  //pink, cyan, and white
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB | LED_FLAG_USE_GLITTER,            .layer = 0, .id0 = 335478784,  .id1 = 16770591,   .r = 255, .g = 20,  .b = 147}, //pink
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 0, .id0 = 2147483648, .id1 = 487,        .r = 0,   .g = 255, .b = 255},  // ASDFJKL: cyan
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB | LED_FLAG_USE_GLITTER,            .layer = 0, .id0 = 201326592,                     .r = 255, .g = 255, .b = 255},  // [] white
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_NULL ,                                     .layer = 0, .id2 = 262136}, //null off
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN ,                       .layer = 0, .id0 = 32767}, //esc-del top row pattern with no glitter
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN | LED_FLAG_USE_GLITTER, .layer = 0, .id0 = 1610645504, .id1 = 4278196224, .id2 = 4294705159, .id3 = 511},
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 262144, .id1 = 3153920,        .r = 0,   .g = 255, .b = 0}, //green
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 131072, .id1 = 2048,           .r = 255, .g = 255, .b = 255}, //white
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 65536,                         .r = 255, .g = 165, .b = 0},  //orange
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 16384, .id1 = 131072,          .r = 255, .g = 0,   .b = 0},  //red
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 33554432,                      .r = 255, .g = 215, .b = 0},  //yellow
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 1, .id1 = 8388736, .id2 = 2,   .r = 0,   .g = 255, .b = 255},  //cyan
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 33554433,                      .r = 52,  .g = 83,  .b = 83},  //dark white/grey
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 16778496, .id2 = 5,            .r = 255, .g = 20,  .b = 147},  //pink
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN | LED_FLAG_USE_GLITTER,        .layer = 1, .id0 = 2113445888, .id1 = 4258133628, .id2 = 7, .pattern_id = 11}, //null off
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN,                               .layer = 1, .id0 = 2147491838, .id1 = 2, .id2 = 4294967288, .id3 = 511, .pattern_id = 2},
    { .end = 1 }
};


led_instruction_t led_game_instructions[] = {   //cyan
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 2147614720, .id1 = 3,      .r = 255,   .g = 20, .b = 147},  //WASD pink
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id1 = 524288,                    .r = 0,   .g = 200, .b = 0},  //M green
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 32798, .id1 = 335548416,   .r = 255, .g = 215, .b = 0},  // 1234,tab,shift,ctrl,alt gold
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 1572864, .id1 = 1036,        .r = 52,  .g = 83,  .b = 83},  //rt dark/dim white
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 327680, .id1 = 57344,      .r = 0,   .g = 180, .b = 180},  //QEZXC cyan
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_NULL,                .layer = 0, .id0 = 1071677408, .id1 = 200739824, .id2 = 262136}, //null off
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN,  .layer = 0, .id2 = 4294705152, .id3 = 511}, //pattern with no glitter
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 262144, .id1 = 3153920,        .r = 0,   .g = 255, .b = 0}, //green
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 131072, .id1 = 2048,           .r = 255, .g = 255, .b = 255}, //white
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 65536,                         .r = 255, .g = 165, .b = 0},  //orange
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 16384, .id1 = 131072,          .r = 255, .g = 0,   .b = 0},  //red
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 33554432,                      .r = 255, .g = 215, .b = 0},  //yellow
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 1, .id1 = 8388736, .id2 = 2,   .r = 0,   .g = 255, .b = 255},  //cyan
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 33554433,                      .r = 52,  .g = 83,  .b = 83},  //dark white/grey
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 16778496, .id2 = 5,            .r = 255, .g = 20,  .b = 147},  //pink
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN | LED_FLAG_USE_GLITTER,        .layer = 1, .id0 = 2113445888, .id1 = 4258133628, .id2 = 7, .pattern_id = 11}, //null off
    {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN,                               .layer = 1, .id0 = 2147491838, .id1 = 2, .id2 = 4294967288, .id3 = 511, .pattern_id = 2},
    { .end = 1 }
};



// led_instruction_t led_instructions[] = {   //purple, green, and black rainbow
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB | LED_FLAG_USE_GLITTER,            .layer = 0, .id0 = 335478784,  .id1 = 16770591,   .r = 148, .g = 0,  .b = 211}, //purple
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 0, .id0 = 2147483648, .id1 = 487,        .r = 0,   .g = 255, .b = 0},  // ASDFJKL: green
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB | LED_FLAG_USE_GLITTER,            .layer = 0, .id0 = 201326592,                     .r = 255, .g = 255, .b = 255},  // [] white
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_NULL ,                                     .layer = 0, .id2 = 262136}, //null off
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN ,                       .layer = 0, .id0 = 32767}, //esc-del top row pattern with no glitter
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN | LED_FLAG_USE_GLITTER, .layer = 0, .id0 = 1610645504, .id1 = 4278196224, .id2 = 4294705159, .id3 = 511},
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 262144, .id1 = 3153920,        .r = 0,   .g = 255, .b = 0}, //green
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 131072, .id1 = 2048,           .r = 255, .g = 255, .b = 255}, //white
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 65536,                         .r = 255, .g = 165, .b = 0},  //orange
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 16384, .id1 = 131072,          .r = 255, .g = 0,   .b = 0},  //red
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 33554432,                      .r = 255, .g = 215, .b = 0},  //yellow
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 1, .id1 = 8388736, .id2 = 2,   .r = 0,   .g = 255, .b = 255},  //cyan
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 33554433,                      .r = 52,  .g = 83,  .b = 83},  //dark white/grey
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 16778496, .id2 = 5,            .r = 255, .g = 20,  .b = 147},  //pink
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN | LED_FLAG_USE_GLITTER,        .layer = 1, .id0 = 2113445888, .id1 = 4258133628, .id2 = 7, .pattern_id = 11}, //null off
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN,                               .layer = 1, .id0 = 2147491838, .id1 = 2, .id2 = 4294967288, .id3 = 511, .pattern_id = 1},
//     { .end = 1 }
// };

//purple
// led_instruction_t led_game_instructions[] = {
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 2147614720, .id1 = 3,      .r = 0,   .g = 255, .b = 0},  //WASD green
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id1 = 524288,                    .r = 0,   .g = 200, .b = 0},  //M green
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 32798, .id1 = 335548416,   .r = 255, .g = 215, .b = 0},  // 1234,tab,shift,ctrl,alt gold
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 1572864, .id1 = 1036,        .r = 52,  .g = 83,  .b = 83},  //rt dark/dim white
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,             .layer = 0, .id0 = 327680, .id1 = 57344,      .r = 148,   .g = 0, .b = 211},  //QEZXC purple
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_NULL,                .layer = 0, .id0 = 1071677408, .id1 = 200739824, .id2 = 262136}, //null off
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_ROTATE_PATTERN,  .layer = 0, .id2 = 4294705152, .id3 = 511}, //pattern with no glitter
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 262144, .id1 = 3153920,        .r = 0,   .g = 255, .b = 0}, //green
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 131072, .id1 = 2048,           .r = 255, .g = 255, .b = 255}, //white
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 65536,                         .r = 255, .g = 165, .b = 0},  //orange
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 16384, .id1 = 131072,          .r = 255, .g = 0,   .b = 0},  //red
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 33554432,                      .r = 255, .g = 215, .b = 0},  //yellow
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id0 = 1, .id1 = 8388736, .id2 = 2,   .r = 0,   .g = 255, .b = 255},  //cyan
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 33554433,                      .r = 52,  .g = 83,  .b = 83},  //dark white/grey
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_RGB,                                   .layer = 1, .id1 = 16778496, .id2 = 5,            .r = 255, .g = 20,  .b = 147},  //pink
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN | LED_FLAG_USE_GLITTER,        .layer = 1, .id0 = 2113445888, .id1 = 4258133628, .id2 = 7, .pattern_id = 11}, //null off
//     {.flags = LED_FLAG_MATCH_LAYER | LED_FLAG_MATCH_ID | LED_FLAG_USE_PATTERN,                               .layer = 1, .id0 = 2147491838, .id1 = 2, .id2 = 4294967288, .id3 = 511, .pattern_id = 1},
//     { .end = 1 }
// };
