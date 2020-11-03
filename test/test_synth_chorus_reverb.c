
#include "test.h"
#include "fluidsynth.h"

// this test should make sure that effects change (reverb, chorus) are handled correctly
int main(void)
{
    fluid_synth_t *synth;
    fluid_settings_t *settings = new_fluid_settings();
    double value;

    TEST_ASSERT(settings != NULL);
    /* set 2 group of effects */
    TEST_SUCCESS(fluid_settings_setint(settings, "synth.effects-groups", 2));

    /* set values for all reverb group */
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.room-size", 0.1));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.damp", 0.2));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.width", 0.3));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.level", 0.4));

    /* set values for all chorus group */
    TEST_SUCCESS(fluid_settings_setint(settings, "synth.chorus.nr", 99));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.chorus.level", 0.5));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.chorus.speed", 0.6));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.chorus.depth", 0.7));

    synth = new_fluid_synth(settings);
    TEST_ASSERT(synth != NULL);

    /*
       check that the synth is initialized with the correct values (for all reverb group)
    */
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_ROOMSIZE, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.1);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_DAMP, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.2);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_WIDTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.3);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.4);

    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_NR, &value) == FLUID_OK);
    TEST_ASSERT((int)value == 99);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.5);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_SPEED, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.6);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_DEPTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.7);

    // update the realtime settings for all reverb group and all chorus group afterward
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.room-size", 0.11));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.damp", 0.22));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.width", 0.33));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.reverb.level", 0.44));

    TEST_SUCCESS(fluid_settings_setint(settings, "synth.chorus.nr", 11));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.chorus.level", 0.55));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.chorus.speed", 0.66));
    TEST_SUCCESS(fluid_settings_setnum(settings, "synth.chorus.depth", 0.77));

    // check that the realtime settings correctly update the values in the synth
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_ROOMSIZE, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.11);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_DAMP, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.22);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_WIDTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.33);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, -1, FLUID_REVERB_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.44);

    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_NR, &value) == FLUID_OK);
    TEST_ASSERT((int)value == 11);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.55);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_SPEED, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.66);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, -1, FLUID_CHORUS_DEPTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.77);

    /*
       Set/get that the synth is initialized with the correct values for one group only
       calling fx set/get API
    */
    // test reverb group 0
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 0, FLUID_REVERB_ROOMSIZE, 0.1110) == FLUID_OK);
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 0, FLUID_REVERB_DAMP, 0.2220) == FLUID_OK);
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 0, FLUID_REVERB_WIDTH, 0.3330) == FLUID_OK);
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 0, FLUID_REVERB_LEVEL, 0.4440) == FLUID_OK);

    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 0, FLUID_REVERB_ROOMSIZE, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.1110);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 0, FLUID_REVERB_DAMP, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.2220);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 0, FLUID_REVERB_WIDTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.3330);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 0, FLUID_REVERB_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.4440);

    // test reverb group 1
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 1, FLUID_REVERB_ROOMSIZE, 0.1111) == FLUID_OK);
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 1, FLUID_REVERB_DAMP, 0.2221) == FLUID_OK);
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 1, FLUID_REVERB_WIDTH, 0.3331) == FLUID_OK);
    TEST_ASSERT(fluid_synth_reverb_set_param(synth, 1, FLUID_REVERB_LEVEL, 0.4441) == FLUID_OK);

    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 1, FLUID_REVERB_ROOMSIZE, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.1111);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 1, FLUID_REVERB_DAMP, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.2221);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 1, FLUID_REVERB_WIDTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.3331);
    TEST_ASSERT(fluid_synth_reverb_get_param(synth, 1, FLUID_REVERB_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.4441);

    // test chorus group 0
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 0, FLUID_CHORUS_NR, 20) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 0, FLUID_CHORUS_LEVEL, 0.5550) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 0, FLUID_CHORUS_SPEED, 0.6660) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 0, FLUID_CHORUS_DEPTH, 0.7770) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 0, FLUID_CHORUS_TYPE, 0) == FLUID_OK);

	TEST_ASSERT(fluid_synth_chorus_get_param(synth, 0, FLUID_CHORUS_NR, &value) == FLUID_OK);
    TEST_ASSERT((int)value == 20);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 0, FLUID_CHORUS_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.5550);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 0, FLUID_CHORUS_SPEED, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.6660);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 0, FLUID_CHORUS_DEPTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.7770);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 0, FLUID_CHORUS_TYPE, &value) == FLUID_OK);
    TEST_ASSERT(value == 0);

    // test chorus group 1
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 1, FLUID_CHORUS_NR, 21) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 1, FLUID_CHORUS_LEVEL, 0.5551) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 1, FLUID_CHORUS_SPEED, 0.6661) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 1, FLUID_CHORUS_DEPTH, 0.7771) == FLUID_OK);
    TEST_ASSERT(fluid_synth_chorus_set_param(synth, 1, FLUID_CHORUS_TYPE, 1) == FLUID_OK);

    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 1, FLUID_CHORUS_NR, &value) == FLUID_OK);
    TEST_ASSERT((int)value == 21);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 1, FLUID_CHORUS_LEVEL, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.5551);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 1, FLUID_CHORUS_SPEED, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.6661);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 1, FLUID_CHORUS_DEPTH, &value) == FLUID_OK);
    TEST_ASSERT(value == 0.7771);
    TEST_ASSERT(fluid_synth_chorus_get_param(synth, 1, FLUID_CHORUS_TYPE, &value) == FLUID_OK);
    TEST_ASSERT(value == 1);

    delete_fluid_synth(synth);
    delete_fluid_settings(settings);

    return EXIT_SUCCESS;
}
