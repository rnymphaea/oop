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
    std::cout << "Saving...\n";
    out << "Count ships\n";
    out << std::to_string(countShips)+"\n";
    out << "Player ships\n";
    for (int i = 0; i < countShips; i++) {
        out << pships[i]->getInfo() << std::endl;
    }
    out << "Computer ships\n";
    for (int i = 0; i < countShips; i++) {
        out << cships[i]->getInfo() << std::endl;
    }
    out << "Player map\n";
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            auto cell = pm->getCell({x, y});
            out << static_cast<char>(cell->getValue()) << "" << std::to_string(static_cast<int>(cell->isVisible())) << " ";
        }
        out << std::endl;
    }
    out << "Computer map\n";
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            auto cell = cm->getCell({x, y});
            out << static_cast<char>(cell->getValue()) << "" << std::to_string(static_cast<int>(cell->isVisible())) << " ";
        }
        out << std::endl;
    }
    out << "Abilities" << std::endl;
    out << am->getInfo();
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
    std::string line;

    while (std::getline(in, line) && line != "Count ships") {}
    int countShips;
    in >> countShips;
    std::cout << "Count ships " << countShips << std::endl;

    state.playerField = std::make_shared<Field>();
    state.compField = std::make_shared<Field>();

    while (std::getline(in, line) && line != "Player ships") {}
    std::vector<std::shared_ptr<Ship>> tmpPlayerShips;
    for (int i = 0; i < countShips; i++) {
        std::getline(in, line);
        std::vector<std::string> splitLine = splitString(line);
        int size = std::stoi(splitLine[0]);
        state.sizes.push_back(size);
        Orientation orient = static_cast<Orientation>(std::stoi(splitLine[1]));
        int x = std::stoi(splitLine[2]);
        int y = std::stoi(splitLine[3]);
        auto ship = std::make_shared<Ship>(size, orient, Coordinates{x, y});
        tmpPlayerShips.push_back(ship);
        state.playerField->placeShip(Coordinates{x,y}, ship, orient);
    }
    while (std::getline(in, line) && line != "Computer ships") {}
    std::vector<std::shared_ptr<Ship>> tmpCompShips;
    for (int i = 0; i < countShips; i++) {
        std::getline(in, line);
        std::vector<std::string> splitLine = splitString(line);
        int size = std::stoi(splitLine[0]);
        Orientation orient = static_cast<Orientation>(std::stoi(splitLine[1]));
        int x = std::stoi(splitLine[2]);
        int y = std::stoi(splitLine[3]);
        auto ship = std::make_shared<Ship>(size, orient, Coordinates{x, y});
        tmpCompShips.push_back(ship);
        state.compField->placeShip(Coordinates{x,y}, ship, orient);
    }

    state.playerShipManager = std::make_shared<ShipManager>(tmpPlayerShips);
    state.compShipManager = std::make_shared<ShipManager>(tmpCompShips);


    while (std::getline(in, line) && line != "Player map") {}
    for (int y = 0; y < 10; y++) {
        std::getline(in, line);
        std::vector<std::string> splitLine = splitString(line);
        for (int x = 0; x < 10; x++) {
            state.playerField->loadCellValue(
                    Coordinates{x, y},
                    charToCellValue(splitLine[x][0]),
                    static_cast<bool>(splitLine[x][1])
                    );
        }
    }

    while (std::getline(in, line) && line != "Computer map") {}
    for (int y = 0; y < 10; y++) {
        std::getline(in, line);
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


    while (std::getline(in, line) && line != "Abilities") {}

    std::string abilitiesInfo;
    std::getline(in, abilitiesInfo);
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
    std::cout << "=============== Your field after loading ===============\n";
    playerField->printField();
    std::cout << "=============== Computer's field after loading ===============\n";
    compField->printField();
}

//void GameState::save(const std::string& filename) {
//    std::ofstream f(filename + ".txt");
//    if (!f.is_open()) {
//        std::cout << "Ошибка открытия файла " + filename + ".txt\n";
//    }
//    f << *this;
//    f.close();
//}
//
//void GameState::load(const std::string& filename) {
//    std::ifstream f(filename + ".txt");
//    if (!f.is_open()) {
//        std::cout << "Ошибка открытия файла " + filename + ".txt\n";
//    }
//    f >> *this;
//    f.close();
//    std::cout << "=============== Your field after loading ===============\n";
//    playerField->printField();
//    std::cout << "=============== Computer's field after loading ===============\n";
//    compField->printField();
//}

std::vector<int> GameState::getSizes() {
    return sizes;
}
