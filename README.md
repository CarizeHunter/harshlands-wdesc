# Harshlands `wdesc` Proposal

A proposed `customize` option for Harshlands MUD that lets eligible
crafters add a short inscription to an item, such as a maker's mark,
a dedication, or a few words on a plaque.

## How it would work

- The crafter chooses a script and language they can write in and pays
  a customization fee. Suggested cost is 3% of the item's value, with
  a minimum of 1 farthing.
- `look <object>` shows that the item bears an inscription.
- `read <object>` reveals the words if the reader can read the script
  and understands the language.

This gives crafters a way to include actual writing while following
the current guidelines for object descriptions and materials.

## C++ mockup

[HL_Wdesc_Mockup.cpp](HL_Wdesc_Mockup.cpp) sketches how `wdesc` could
fit into the existing customization, payment, and literacy systems.
