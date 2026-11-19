#include <optional>
#include <string>

// Add std::optional<Inscription> inscription to each item instance.
// Older items load with an empty inscription field.
struct Inscription {
    ScriptId script;
    LanguageId language;
    std::string text;
};

void customizeWdesc(Character& crafter, Item& item,
                    ScriptId script, LanguageId language,
                    const std::string& words)
{
    // Apply the usual CUSTOMIZE rules for the crafter and item.
    if (!canCustomize(crafter, item)) {
        send(crafter, "You cannot customize that item.");
        return;
    }

    if (!isValidScriptForLanguage(script, language)) {
        send(crafter, "That script cannot be used for this language.");
        return;
    }

    if (!canWrite(crafter, script, language)) {
        send(crafter, "You lack the skill to write that inscription.");
        return;
    }

    if (!isValidShortInscription(words)) {
        send(crafter, "Enter a short, single-line inscription.");
        return;
    }

    const int fee = customizationFee(item, /*percent=*/3,
                                    /*minimumFarthings=*/1);

    // Deduct the fee and save the inscription together. If either fails,
    // preserve the crafter's balance and any previous inscription.
    if (!chargeAndSaveInscription(crafter, item, fee,
                                  Inscription{script, language, words})) {
        send(crafter, "The inscription could not be saved. No fee was charged.");
        return;
    }

    send(crafter, "You add the inscription.");
}

// Called from LOOK after displaying the item's detailed description.
void showWdesc(Character& viewer, const Item& item)
{
    if (item.inscription) {
        send(viewer, "It bears an inscription.");
    }
}

// Called from READ after resolving an item the character can examine.
// Returning false lets READ continue handling other kinds of writing.
bool readWdesc(Character& reader, const Item& item)
{
    if (!item.inscription) {
        return false;
    }

    const Inscription& inscription = *item.inscription;

    if (!canReadScript(reader, inscription.script)) {
        send(reader, "You cannot read the lettering.");
        return true;
    }

    if (!understandsLanguage(reader, inscription.language)) {
        send(reader, "You recognize the script but cannot make out the words.");
        return true;
    }

    send(reader, "The inscription reads, \"" + inscription.text + "\"");
    return true;
}
