#include "../include/GameState.h"

GameState::GameState(std::vector<int> lengths)
        : sizes(lengths),
          playerShipManager(std::make_shared<ShipManager>(lengths)),
          compShipManager(std::make_shared<ShipManager>(lengths)),
          abilityManager(std::make_shared<AbilityManager>()),
          playerField(std::make_shared<Field>()),
          compField(std::make_shared<Field>()) { }

std::shared_ptr<ShipManager> GameState::getPlayerShipManager() const {
    return playerShipManager;
}

std::shared_ptr<ShipManager> GameState::getCompShipManager() const {
    return compShipManager;
}

std::shared_ptr<AbilityManager> GameState::getAbilityManager() const {
    return abilityManager;
}

std::shared_ptr<Field> GameState::getPlayerField() const {
    return playerField;
}

std::shared_ptr<Field> GameState::getCompField() const {
    return compField;
}

void GameState::newCompShipManager() {
    compShipManager = std::make_shared<ShipManager>(sizes);
}

void GameState::newCompField() {
    compField = std::make_shared<Field>();
}

std::ostream &operator<<(std::ostream &out, const GameState &state) {
    auto psm = state.getPlayerShipManager();
    auto csm = state.getCompShipManager();
    auto pm = state.getPlayerField();
    auto cm = state.getCompField();
    auto am = state.getAbilityManager();
    auto pships = psm->getShips();
    auto cships = csm->getShips();
    int countShips = pships.size();

    // Для накопления данных перед хэшированием
    std::ostringstream buffer;
    buffer << "Count ships\n";
    buffer << std::to_string(countShips) + "\n";

    buffer << "Player ships\n";
    for (int i = 0; i < countShips; i++) {
        buffer << pships[i]->getInfo() << std::endl;
    }

    buffer << "Computer ships\n";
    for (int i = 0; i < countShips; i++) {
        buffer << cships[i]->getInfo() << std::endl;
    }

    buffer << "Player map\n";
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            auto cell = pm->getCell({x, y});
            buffer << static_cast<char>(cell->getValue()) << ""
                   << std::to_string(static_cast<int>(cell->isVisible())) << " ";
        }
        buffer << std::endl;
    }

    buffer << "Computer map\n";
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            auto cell = cm->getCell({x, y});
            buffer << static_cast<char>(cell->getValue()) << ""
                   << std::to_string(static_cast<int>(cell->isVisible())) << " ";
        }
        buffer << std::endl;
    }

    buffer << "Abilities" << std::endl;
    buffer << am->getInfo();
    buffer << std::endl;

    std::string data = buffer.str();
    std::hash<std::string> hasher;
    size_t checksum = hasher(data);

    out << data;

    out << "Checksum: " << checksum << std::endl;

    return out;
}

std::vector<std::string> splitString(const std::string& inputLine) {
    std::vector<std::string> result;
    std::istringstream stream(inputLine);
    std::string part;

    while (stream >> part) {
        result.push_back(part);
    }

    return result;
}

CellValue charToCellValue(char c) {
    switch (c) {
        case '.': return CellValue::Empty;
        case 'S': return CellValue::Segment;
        case 'W': return CellValue::Hit;
        case 'X': return CellValue::Destroyed;
    }
}

std::istream &operator>>(std::istream &in, GameState &state) {
    std::cout << "Loading...\n";

    std::ostringstream buffer;
    std::string line;

    while (std::getline(in, line)) {
        if (line.rfind("Checksum:", 0) == 0) {
            break;
        }
        buffer << line << "\n";
    }

    if (line.rfind("Checksum:", 0) != 0) {
        throw std::runtime_error("Ошибка: контрольная сумма не найдена в файле.");
    }

    size_t fileChecksum = std::stoull(line.substr(9)); // пропускаем "Checksum: "

    std::string data = buffer.str();
    std::hash<std::string> hasher;
    size_t calculatedChecksum = hasher(data);

    if (fileChecksum != calculatedChecksum) {
        throw std::runtime_error("Ошибка: контрольная сумма не совпадает. Данные повреждены.");
    }

    std::istringstream validData(data);

    while (std::getline(validData, line) && line != "Count ships") {}
    int countShips;
    validData >> countShips;

    state.playerField = std::make_shared<Field>();
    state.compField = std::make_shared<Field>();

    while (std::getline(validData, line) && line != "Player ships") {}
    std::vector<std::shared_ptr<Ship>> tmpPlayerShips;
    for (int i = 0; i < countShips; i++) {
        std::getline(validData, line);
        std::vector<std::string> splitLine = splitString(line);
        int size = std::stoi(splitLine[0]);
        state.sizes.push_back(size);
        Orientation orient = static_cast<Orientation>(std::stoi(splitLine[1]));
        int x = std::stoi(splitLine[2]);
        int y = std::stoi(splitLine[3]);
        auto ship = std::make_shared<Ship>(size, orient, Coordinates{x, y});
        tmpPlayerShips.push_back(ship);
        state.playerField->placeShip(Coordinates{x, y}, ship, orient);
    }

    while (std::getline(validData, line) && line != "Computer ships") {}
    std::vector<std::shared_ptr<Ship>> tmpCompShips;
    for (int i = 0; i < countShips; i++) {
        std::getline(validData, line);
        std::vector<std::string> splitLine = splitString(line);
        int size = std::stoi(splitLine[0]);
        Orientation orient = static_cast<Orientation>(std::stoi(splitLine[1]));
        int x = std::stoi(splitLine[2]);
        int y = std::stoi(splitLine[3]);
        auto ship = std::make_shared<Ship>(size, orient, Coordinates{x, y});
        tmpCompShips.push_back(ship);
        state.compField->placeShip(Coordinates{x, y}, ship, orient);
    }

    state.playerShipManager = std::make_shared<ShipManager>(tmpPlayerShips);
    state.compShipManager = std::make_shared<ShipManager>(tmpCompShips);

    while (std::getline(validData, line) && line != "Player map") {}
    for (int y = 0; y < 10; y++) {
        std::getline(validData, line);
        std::vector<std::string> splitLine = splitString(line);
        for (int x = 0; x < 10; x++) {
            state.playerField->loadCellValue(
                    Coordinates{x, y},
                    charToCellValue(splitLine[x][0]),
                    static_cast<bool>(splitLine[x][1])
            );
        }
    }

    while (std::getline(validData, line) && line != "Computer map") {}
    for (int y = 0; y < 10; y++) {
        std::getline(validData, line);
        std::vector<std::string> splitLine = splitString(line);
        for (int x = 0; x < 10; x++) {
            bool visible = splitLine[x][1] == '1';
            state.compField->loadCellValue(
                    Coordinates{x, y},
                    charToCellValue(splitLine[x][0]),
                    visible
            );
        }
    }

    while (std::getline(validData, line) && line != "Abilities") {}

    std::string abilitiesInfo;
    std::getline(validData, abilitiesInfo);
    auto info = splitString(abilitiesInfo);
    state.abilityManager = std::make_shared<AbilityManager>(info);
    return in;
}

void GameState::save(const std::string& filename) {
    FileWriter writer(filename + ".txt");
    writer.getOutfile() << *this;
}

void GameState::load(const std::string& filename) {
    FileReader reader(filename + ".txt");
    reader.getInfile() >> *this;
}


std::vector<int> GameState::getSizes() {
    return sizes;
}
