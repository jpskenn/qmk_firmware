/* Copyright 2021 Takeshi Nishio
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "muse.h"
#include <stdlib.h>

static void sequencer_show_playback(bool);
static void sequencer_show_track(uint8_t);
static void sequencer_show_track_deactivated(void);
static void sequencer_show_steps(uint8_t);
static void sequencer_show_tempo_and_resolution(void);
static void set_hsv_by_decimal_index(uint8_t index, uint8_t*, uint8_t*, uint8_t*);
static bool is_sequencer_any_track_active(void);
static void sequencer_generate_random_step(bool);
static void sequencer_increase_step_frame_index(void);
static void sequencer_decrease_step_frame_index(void);

static uint8_t sequencer_step_frame_index = 0;
static bool is_sequencer_step_frame_mode = true;

#ifdef RGBLIGHT_LAYERS
// Indicator LED settings
#define INDICATOR_INDEX 0         // Where to start indicator, default:9
#define INDICATOR_COUNT 1         // How many LEDs for indicator, default:1
#define INDICATOR_CHANGE_COUNT 1  // How meny LEDs to change for temporally layer default:1
#define INDICATOR_DIMMER 150          // LED brightness dimmer level, 0(brightest) - 255(perfect dark), default:150
#endif

// LED position
#define LED_RE0_INDEX 1
#define LED_RE1_INDEX 3
#define LED_RE2_INDEX 4
#define LED_RE3_INDEX 5
#define LED_RE4_INDEX 6

// Sequencer settings
#define SEQ_PLAYBACK_INDICATOR_INDEX 2  // Where to start playback indicator, default:2
#define SEQ_TRACK_INDICATOR_INDEX 1     // Where to start track indicator, default:1
#define SEQ_TRACK_DEACTIVATED_COLOR_INDEX 9 // The color index in set_hsv_by_decimal_index(), default:9(=white)
#define SEQ_LED_DIMMER 100              // Sequencer LED brightness dimmer level, 0(brightest) - 255(perfect dark), default:100
#define SEQ_LED_DARK_DIMMER 220     // Step Off LED brightness dimmer level, 0(brightest) - 255(perfect dark), default:200
#define SEQ_TEMPO 100                   // Sequencer initial tempo, default:100

// Layer index
enum layer_number {
    _MAC = 0,
    _WIN,
    _MIDI,
    _SEQUENCER,
    _LOWER,
    _RAISE,
    _ADJUST,
    _CAPS,          // This is not a "REAL" layer. Define here to use for RGB light layer.
};

// Sequencer Track note, General MIDI Drum mapping
const uint16_t unison_sequencer_track_notes[SEQUENCER_TRACKS] = {
    MI_C_1,     // Kick
    MI_D_1,     // Snare
    MI_Fs_1,    // Hi-Hat Closed
    MI_As_1,    // Hi-Hat Open
    MI_Cs_2,    // Crash
    MI_Ds_2,    // Ride
    MI_D_2,     // High Tom
    MI_A_1,     // Low Tom
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MAC = SAFE_RANGE,
    WIN,
    MIDI,
    SEQ,
    LOWER,
    RAISE,
    M_PSCR,
    ALT_EN,
    ALT_JA,
    GUI_EN,
    GUI_JA,
    SEQ_FRM,
    SEQ_FRI,
    SEQ_FRD,
    SEQ_TMP,
    SEQ_RES,
    SEQ_RST,
    SEQ_RND,
    SEQ_LRD,
    SEQ_FTG,
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define S_SLS   RSFT_T(KC_SLSH)
#define C_ESC   LCTL_T(KC_ESC)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define SEQ     DF(_SEQUENCER)
#define ALT_EN  LALT_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define GUI_JA  LGUI_T(KC_LANG1)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT_music(
                        KC_MUTE,        KC_F1,  KC_F2,  KC_F3,  KC_F4,          KC_MUTE,        KC_MUTE,        KC_MUTE,        KC_MUTE,
        KC_P7,  KC_P8,  KC_P9,  KC_PSLS,KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       KC_BSPC,
        KC_P4,  KC_P5,  KC_P6,  KC_PAST,C_ESC,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,    KC_ENT,
        KC_P1,  KC_P2,  KC_P3,  KC_PMNS,KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, S_SLS,  KC_UP,
        KC_P0,  KC_PDOT,KC_PENT,KC_PPLS,KC_GRV, KC_BSLS,ALT_JA, GUI_EN, SP_LOW, SP_LOW, KC_SPC, SP_RAI, SP_RAI, KC_RCTL,KC_LEFT,KC_RGHT,KC_DOWN
    ),
    [_WIN] = LAYOUT_music(
                        _______,        _______,_______,_______,_______,        _______,        _______,        _______,        _______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,_______,_______,GUI_JA, ALT_EN, _______,_______,_______,_______,_______,KC_APP,_______,_______,_______
    ),
    [_MIDI] = LAYOUT_music(
                          KC_MUTE,          KC_SPC,  KC_ENT,  KC_COMM, KC_DOT,           MI_VEL_9,         MI_OCT_0,         MI_TRNS_0,        MI_CH1,
        MI_CHD,  MI_CH1,  MI_CHU,  XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,
        MI_TRNSD,MI_TRNS_0,MI_TRNSU,MI_Fs_1,    MI_Gs_1, MI_As_1, XXXXXXX, MI_Cs_2, MI_Ds_2, XXXXXXX, MI_Fs_2, MI_Gs_2, MI_As_2, XXXXXXX, MI_Cs_3,      MI_Ds_3,
        MI_OCTD, MI_OCT_0,MI_OCTU, MI_F_1,  MI_G_1,  MI_A_1,  MI_B_1,  MI_C_2,  MI_D_2,  MI_E_2,  MI_F_2,  MI_G_2,  MI_A_2,  MI_B_2,  MI_C_3,  MI_D_3,  MI_E_3,
        MI_VELD, MI_VEL_9,MI_VELU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   LOWER,   XXXXXXX, RAISE,   RAISE,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_SEQUENCER] = LAYOUT_music(
                          KC_MUTE,          SQ_TOG,  SEQ_FTG, SEQ_FRD, SEQ_FRI,          SEQ_TMP,          SEQ_RES,          XXXXXXX,          SEQ_FRM,
        SQ_S(0), SQ_S(1), SQ_S(2), SQ_S(3),     SQ_S(4), SQ_S(5), SQ_S(6), SQ_S(7), SQ_S(8), SQ_S(9), SQ_S(10),SQ_S(11),SQ_S(12),SQ_S(13),SQ_S(14),     SQ_S(15),
        SQ_S(16),SQ_S(17),SQ_S(18),SQ_S(19),    SQ_S(20),SQ_S(21),SQ_S(22),SQ_S(23),SQ_S(24),SQ_S(25),SQ_S(26),SQ_S(27),SQ_S(28),SQ_S(29),SQ_S(30),     SQ_S(31),
        SQ_T(0), SQ_T(1), SQ_T(2), SQ_T(3), SQ_T(4), SQ_T(5), SQ_T(6), SQ_T(7), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        SQ_SALL, SQ_SCLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   LOWER,   XXXXXXX, RAISE,   RAISE,   XXXXXXX, XXXXXXX, SEQ_LRD, SEQ_RND
    ),
    [_LOWER] = LAYOUT_music(
                        KC_MUTE,        SEQ,    MAC,    WIN,    MIDI,           KC_MUTE,        KC_MUTE,        KC_MUTE,        KC_MUTE,
        KC_NLCK,KC_PSLS,KC_PSLS,KC_PAST,KC_TILD,    KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,    KC_DEL,
        _______,_______,_______,_______,_______,    _______,_______,_______,_______,_______,KC_GRV, KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,    KC_BSLS,
        _______,_______,_______,_______,_______,_______,KC_PSCR,KC_SLCK,KC_PAUS,_______,_______,KC_TILD,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
        _______,_______,_______,_______,_______,_______,KC_APP ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    ),
    [_RAISE] = LAYOUT_music(
                        KC_MUTE,        SEQ,    MAC,    WIN,    MIDI,           KC_MUTE,        KC_MUTE,        KC_MUTE,        KC_MUTE,
        KC_NLCK,KC_PSLS,KC_PSLS,KC_PAST,KC_GRV,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,       KC_DEL,
        _______,_______,_______,_______,_______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SCLN,    KC_QUOT,
        _______,_______,_______,_______,_______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_COLN,KC_DQUO,
        _______,_______,_______,_______,_______,_______,KC_F11, KC_F12, _______,_______,_______,_______,_______,_______,_______,_______,_______
    ),
    [_ADJUST] = LAYOUT_music(
                        KC_MUTE,        SEQ,    MAC,    WIN,    MIDI,           KC_MUTE,        KC_MUTE,        KC_MUTE,        KC_MUTE,
        _______,_______,_______,_______,_______,    _______,_______,_______,RESET,  _______,RGB_HUI,RGB_SAI,RGB_VAI,_______,RGB_RMOD,   _______,
        _______,_______,_______,_______,_______,    AU_TOG, CK_TOGG,MU_TOG, MU_MOD, _______,RGB_HUD,RGB_SAD,RGB_VAD,RGB_TOG,RGB_MOD,    _______,
        _______,_______,_______,_______,KC_CAPS,KC_CAPS,CK_RST, CK_DOWN,CK_UP,  _______,_______,_______,_______,_______,_______,_______,_______,
        _______,SEQ_RST,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC:
            if (record->event.pressed) {
                // revert LED animation, turned off by SEQ
                rgblight_reload_from_eeprom();
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_MAC);
            }
            return false;
            break;
        case WIN:
            if (record->event.pressed) {
                // revert LED animation, turned off by SEQ
                rgblight_reload_from_eeprom();
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_WIN);
            }
            return false;
            break;
        case MIDI:
            if (record->event.pressed) {
                // revert LED animation, turned off by SEQ
                rgblight_reload_from_eeprom();
                // Change default layer --> Write to EEPROM
                set_single_persistent_default_layer(_MIDI);
            }
            return false;
            break;
        case SEQ:
            if (record->event.pressed) {
                // Stop LED animation and turn off all LEDs for step and track display.
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                rgblight_sethsv_noeeprom(HSV_BLACK);
            }
            break;
        case SEQUENCER_TRACK_MIN ... SEQUENCER_TRACK_MAX:
            if (record->event.pressed) {
                if (!is_sequencer_track_active(keycode - SEQUENCER_TRACK_MIN)) { // At this point, the activate state is not changed yet.
                    sequencer_step_frame_index = 0;
                }
                if (!is_sequencer_on()) {
                    is_sequencer_step_frame_mode = true;
                }
            }
            break;
        case SEQ_FRM: // Reset display frame index to the head.
            if (record->event.pressed) {
                sequencer_step_frame_index = 0;
            }
            return false;
            break;
        case SEQ_TMP: // Reset sequencer tempo.
            if (record->event.pressed) {
                sequencer_set_tempo(SEQ_TEMPO);
            }
            if (!is_sequencer_on() && !is_sequencer_any_track_active()) {
                sequencer_show_tempo_and_resolution();
            }
            return false;
            break;
        case SEQ_RES: // Reset sequencer resolution.
            if (record->event.pressed) {
                sequencer_set_resolution(SQ_RES_4);
            }
            if (!is_sequencer_on() && !is_sequencer_any_track_active()) {
                sequencer_show_tempo_and_resolution();
            }
            return false;
            break;
        case SEQ_RST: // Turn off all steps on all track.
            if (record->event.pressed) {
                for (uint8_t track = 0; track < SEQUENCER_TRACKS; track++) {
                    sequencer_activate_track(track);
                    sequencer_set_all_steps_off();
                    sequencer_deactivate_track(track);
                }
            }
            return false;
            break;
        case SEQ_RND: // Generate random step
            if (record->event.pressed) {
                sequencer_generate_random_step(true);
            }
            return false;
            break;
        case SEQ_LRD: // Generate random step, lightly
            if (record->event.pressed) {
                sequencer_generate_random_step(false);
            }
            return false;
            break;
        case SEQ_FTG: // Toggle step frame display mode.
            if (record->event.pressed) {
                is_sequencer_step_frame_mode = !is_sequencer_step_frame_mode;
            }
            return false;
            break;
        case SEQ_FRI: // Increase step frame index
            if (record->event.pressed) {
                sequencer_increase_step_frame_index();
            }
            return false;
            break;
        case SEQ_FRD: // Decrease step frame index
            if (record->event.pressed) {
                sequencer_decrease_step_frame_index();
            }
            return false;
            break;
        case M_PSCR: // provide Mac's advanced screen capture
            if (record->event.pressed) {
                switch(biton32(default_layer_state)) {
                case _WIN:
                    tap_code(KC_PSCR);
                    break;
                default:
                    tap_code16(LSFT(LGUI(KC_5)));
                    break;
                }
            }
            break;
        default:
            break;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SQ_TOG:
            if (!record->event.pressed) {
                is_sequencer_step_frame_mode = !is_sequencer_on();
            }
            break;
        default:
            break;
    }
}


/* ------------------------------------------------------------------------------
   Sequencer
------------------------------------------------------------------------------ */
void sequencer_show_playback(bool is_sequencer_on) {
    if (is_sequencer_on) {
        rgblight_sethsv_at(HSV_CHARTREUSE - INDICATOR_DIMMER, SEQ_PLAYBACK_INDICATOR_INDEX);
    } else {
        rgblight_sethsv_at(HSV_SPRINGGREEN - INDICATOR_DIMMER, SEQ_PLAYBACK_INDICATOR_INDEX);
    }
}

bool is_sequencer_any_track_active() {
    for (uint8_t track = 0; track < SEQUENCER_TRACKS; track++) {
        if (is_sequencer_track_active(track)) {
            return true;
        }
    }

    return false;
}

void sequencer_show_tempo_and_resolution() {
    uint8_t hue = 0;
    uint8_t sat = 0;
    uint8_t val = 0;

    // tempo: 100, hundreds place
    set_hsv_by_decimal_index(sequencer_get_tempo() / 100, &hue, &sat, &val);
    rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE1_INDEX);

    // tempo: 10, tens place
    set_hsv_by_decimal_index(sequencer_get_tempo() / 10 % 10, &hue, &sat, &val);
    rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE2_INDEX);

    // tempo: 1, ones place
    set_hsv_by_decimal_index(sequencer_get_tempo() % 10, &hue, &sat, &val);
    rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE3_INDEX);

    // resolution
    set_hsv_by_decimal_index(sequencer_get_resolution() + 1, &hue, &sat, &val);
    rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE4_INDEX);
}

void set_hsv_by_decimal_index(uint8_t decimal_index, uint8_t *hue, uint8_t *sat, uint8_t *val) {
    switch (decimal_index) {
        case 0: // black
            *hue = 0;
            *sat = 0;
            *val = SEQ_LED_DIMMER;
            break;
        case 1: // red
            *hue = 0;
            *sat = 255;
            *val = 255;
            break;
        case 2: // coral
            *hue = 11;
            *sat = 176;
            *val = 255;;
            break;
        case 3: // orange
            *hue = 28;
            *sat = 255;
            *val = 255;
            break;
        case 4: // green
            *hue = 85;
            *sat = 255;
            *val = 255;
            break;
        case 5: // spring green
            *hue = 106;
            *sat = 255;
            *val = 255;
            break;
        case 6: // blue
            *hue = 170;
            *sat = 255;
            *val = 255;
            break;
        case 7: // purple
            *hue = 191;
            *sat = 255;
            *val = 255;
            break;
        case 8: // magenta
            *hue = 213;
            *sat = 255;
            *val = 255;
            break;
        case 9: // white
            *hue = 0;
            *sat = 0;
            *val = 255;
            break;
    }
}

void sequencer_show_track(uint8_t track) {
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
    set_hsv_by_decimal_index(track + 1, &hue, &sat, &val);
    rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, SEQ_TRACK_INDICATOR_INDEX);
}

void sequencer_show_track_deactivated() {
    sequencer_show_track(SEQ_TRACK_DEACTIVATED_COLOR_INDEX - 1);
}

void sequencer_show_steps(uint8_t track) {
    uint8_t hue;
    uint8_t sat;
    uint8_t val;
    set_hsv_by_decimal_index(sequencer_step_frame_index + 1, &hue, &sat, &val);

    if (is_sequencer_step_on(sequencer_step_frame_index * 4 + 0)) {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE1_INDEX);
    } else {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DARK_DIMMER, LED_RE1_INDEX);
    }

    if (is_sequencer_step_on(sequencer_step_frame_index * 4 + 1)) {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE2_INDEX);
    } else {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DARK_DIMMER, LED_RE2_INDEX);
    }

    if (is_sequencer_step_on(sequencer_step_frame_index * 4 + 2)) {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE3_INDEX);
    } else {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DARK_DIMMER, LED_RE3_INDEX);
    }

    if (is_sequencer_step_on(sequencer_step_frame_index * 4 + 3)) {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DIMMER, LED_RE4_INDEX);
    } else {
        rgblight_sethsv_at(hue, sat, val - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
    }
}

void sequencer_generate_random_step(bool is_full_random) {
    uint8_t divider = 2;
    if (!is_full_random) {
        divider = 4;
    }

    for (uint8_t track = 0; track < SEQUENCER_TRACKS; track++) {
        if (is_sequencer_track_active(track)) {
            srand(timer_read());
            for (uint8_t step = 0; step < SEQUENCER_STEPS; step++) {
                if (rand() % divider == 0) {
                    sequencer_toggle_step(step);
                }
            }
        }
    }
}

void sequencer_increase_step_frame_index() {
    if (sequencer_step_frame_index < (SEQUENCER_STEPS / 4 - 1) ) {
        sequencer_step_frame_index++;
    }
}
void sequencer_decrease_step_frame_index() {
    if (sequencer_step_frame_index > 0) {
        sequencer_step_frame_index--;
    }
}


/* ------------------------------------------------------------------------------
   RGB Light Layer settings
------------------------------------------------------------------------------ */
#ifdef RGBLIGHT_LAYERS

// Default layers (= Base layers)
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_WHITE - INDICATOR_DIMMER}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_BLUE - INDICATOR_DIMMER}
);
const rgblight_segment_t PROGMEM my_midi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_ORANGE - INDICATOR_DIMMER}
);
const rgblight_segment_t PROGMEM my_sequencer_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_COUNT, HSV_SPRINGGREEN - INDICATOR_DIMMER}
);

// Temporal layers
const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_GREEN - INDICATOR_DIMMER}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_CYAN - INDICATOR_DIMMER}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_RED - INDICATOR_DIMMER}
);

// Lock indicator
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {INDICATOR_INDEX , INDICATOR_CHANGE_COUNT, HSV_MAGENTA - INDICATOR_DIMMER}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_mac_layer,
    my_win_layer,
    my_midi_layer,
    my_sequencer_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer,
    my_caps_layer
);

// Enabling and disabling lighting layers for temporal layer
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    rgblight_set_layer_state(_LOWER, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(_RAISE, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(_ADJUST, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_MAC, layer_state_cmp(state, _MAC));
    rgblight_set_layer_state(_WIN, layer_state_cmp(state, _WIN));
    rgblight_set_layer_state(_MIDI, layer_state_cmp(state, _MIDI));
    rgblight_set_layer_state(_SEQUENCER, layer_state_cmp(state, _SEQUENCER));

    return state;
}

// Enabling and disabling lighting layers for Lock indicator
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(_CAPS, led_state.caps_lock);
    return true;
}
#endif


/* ------------------------------------------------------------------------------
   Rotary Encoder
------------------------------------------------------------------------------ */
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* 1st encoder, Left side */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) { /* 2nd encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    if (midi_config.velocity < 127) {
                        if (midi_config.velocity < 115) {
                            midi_config.velocity += 13;
                        } else {
                            midi_config.velocity = 127;
                        }
                    }
                } else {
                    if (midi_config.velocity > 0) {
                        if (midi_config.velocity == 127) {
                            midi_config.velocity -= 10;
                        } else if (midi_config.velocity > 12) {
                            midi_config.velocity -= 13;
                        } else {
                            midi_config.velocity = 0;
                        }
                    }
                }
                break;
            case _SEQUENCER:
                if (clockwise) {
                    sequencer_increase_tempo();
                } else {
                    sequencer_decrease_tempo();
                }
                break;
            default:
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
        }
    } else if (index == 2) { /* 3rd encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    if (midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN - 2)) {
                        midi_config.octave++;
                    }
                } else {
                    if (midi_config.octave > 0) {
                        midi_config.octave--;
                    }
                }
                break;
            case _SEQUENCER:
                if (clockwise) {
                    sequencer_increase_resolution();
                } else {
                    sequencer_decrease_resolution();
                }
                break;
            default:
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
        }
    } else if (index == 3) { /* 4th encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    if (midi_config.transpose < (MIDI_TRANSPOSE_MAX - MI_TRNS_0)) {
                        const bool positive = midi_config.transpose > 0;
                        midi_config.transpose++;
                        if (positive && midi_config.transpose < 0) {
                            midi_config.transpose--;
                        }
                    }
                } else {
                    if (midi_config.transpose > (MIDI_TRANSPOSE_MIN - MI_TRNS_0)) {
                        midi_config.transpose--;
                    }
                }
                break;
            case _SEQUENCER:
                break;
            default:
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
        }
    } else if (index == 4) { /* 5th encoder, Right side */
        switch(biton32(default_layer_state)) {
            case _MIDI:
                if (clockwise) {
                    midi_config.channel++;
                } else {
                    midi_config.channel--;
                }
                break;
            case _SEQUENCER:
                if (clockwise) {
                    sequencer_increase_step_frame_index();
                } else {
                    sequencer_decrease_step_frame_index();
                }
                break;
            default:
                if (clockwise) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
                break;
        }
    }
}
#endif


/* ------------------------------------------------------------------------------
   Post Initialize
------------------------------------------------------------------------------ */
void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_LAYERS
    // RGB Lighting Layers: Setup LED layers
    rgblight_layers = my_rgb_layers;
    #endif

    // MIDI & Sequencer: Reset the octave offset to 0
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;

    // Sequencer: use defined notes
    sequencer_set_track_notes(unison_sequencer_track_notes);

    // Sequencer: set initial tempo
    sequencer_set_tempo(SEQ_TEMPO);
}


/* ------------------------------------------------------------------------------
   Matrix Scan
------------------------------------------------------------------------------ */
void matrix_scan_user(void) {
    if (biton32(default_layer_state) == _SEQUENCER) {
        uint8_t track;
        bool is_track_active = false;

        for (track = 0; track < SEQUENCER_TRACKS; track++) {
            if (is_sequencer_track_active(track)) {
                sequencer_show_track(track);
                is_track_active = true;
                break;
            }
        }

        if (!is_track_active) {
            sequencer_show_track_deactivated();
        }

        if (is_sequencer_step_frame_mode) {
            if (is_track_active) {
                sequencer_show_steps(track);
            } else {
                sequencer_show_tempo_and_resolution();
            }
        } else {
            switch (sequencer_get_current_step()) {
            case 0:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_CORAL - SEQ_LED_DARK_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_ORANGE - SEQ_LED_DARK_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_GREEN - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
                break;
            case 4:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_CORAL - SEQ_LED_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_ORANGE - SEQ_LED_DARK_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_GREEN - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
                break;
            case 8:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_CORAL - SEQ_LED_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_ORANGE - SEQ_LED_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_GREEN - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
                break;
            case 12:
                rgblight_sethsv_at(HSV_RED - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_CORAL - SEQ_LED_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_ORANGE - SEQ_LED_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_GREEN - SEQ_LED_DIMMER, LED_RE4_INDEX);
                break;
            case 16:
                rgblight_sethsv_at(HSV_SPRINGGREEN - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DARK_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_PURPLE - SEQ_LED_DARK_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_MAGENTA - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
                break;
            case 20:
                rgblight_sethsv_at(HSV_SPRINGGREEN - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_PURPLE - SEQ_LED_DARK_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_MAGENTA - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
                break;
            case 24:
                rgblight_sethsv_at(HSV_SPRINGGREEN - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_PURPLE - SEQ_LED_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_MAGENTA - SEQ_LED_DARK_DIMMER, LED_RE4_INDEX);
                break;
            case 28:
                rgblight_sethsv_at(HSV_SPRINGGREEN - SEQ_LED_DIMMER, LED_RE1_INDEX);
                rgblight_sethsv_at(HSV_BLUE - SEQ_LED_DIMMER, LED_RE2_INDEX);
                rgblight_sethsv_at(HSV_PURPLE - SEQ_LED_DIMMER, LED_RE3_INDEX);
                rgblight_sethsv_at(HSV_MAGENTA - SEQ_LED_DIMMER, LED_RE4_INDEX);
                break;
            }
        }

        if (is_sequencer_on()) {
            sequencer_show_playback(true);
        } else {
            sequencer_show_playback(false);
        }
    }
}
