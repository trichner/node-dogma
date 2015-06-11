

/*

 int main(void) {
 dogma_context_t* ctx;
 double value;

 assert(dogma_init() == DOGMA_OK);
 assert(dogma_init_context(&ctx) == DOGMA_OK);

 assert(dogma_set_ship(ctx, TYPE_Rifter) == DOGMA_OK);

 assert(dogma_get_ship_attribute(ctx, ATT_HiSlots, &value) == DOGMA_OK);
 assert(value == 4);
 assert(dogma_get_ship_attribute(ctx, ATT_MedSlots, &value) == DOGMA_OK);
 assert(value == 3);
 assert(dogma_get_ship_attribute(ctx, ATT_LowSlots, &value) == DOGMA_OK);
 assert(value == 3);
 assert(dogma_get_ship_attribute(ctx, ATT_UpgradeSlotsLeft, &value) == DOGMA_OK);
 assert(value == 3);
 assert(dogma_get_ship_attribute(ctx, ATT_MaxSubSystems, &value) == DOGMA_OK);
 assert(value == 0);

 assert(dogma_free_context(ctx) == DOGMA_OK);
 return 0;
 }
 */