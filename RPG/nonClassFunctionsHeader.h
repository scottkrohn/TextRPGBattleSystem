void SeedRandom();
int DamageChangeAmount(std::size_t variancePercent);
PlayerCharacterBase * CreatePlayerCharacter(const std::string name, const std::size_t jobType);
void HandleInvalidInput(std::istream &inputStream);