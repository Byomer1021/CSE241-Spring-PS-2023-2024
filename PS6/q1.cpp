#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>
#include <random>  // Include for std::random_device and std::mt19937
#include <algorithm>



using namespace std;

const int GRID_SIZE = 20;
const int ANT_BREED = 3;
const int DOODLEBUG_BREED = 8;
const int DOODLEBUG_STARVE = 3;

enum class OrganismType { EMPTY, ANT, DOODLEBUG };

class World;

class Organism {
public:
    Organism(World* world, int x, int y) : world(world), x(x), y(y), moved(false), steps(0) {}
    virtual ~Organism() {}

    virtual void move() = 0;
    virtual void breed() = 0;
    virtual OrganismType getType() const = 0;
    virtual bool starve() { return false; }

    void setMoved(bool hasMoved) { moved = hasMoved; }
    bool hasMoved() const { return moved; }
    void incrementSteps() { ++steps; }
    int getSteps() const { return steps; }

protected:
    World* world;
    int x;
    int y;
    bool moved;
    int steps;
};

class Ant : public Organism {
public:
    Ant(World* world, int x, int y) : Organism(world, x, y) {}
    void move() override;
    void breed() override;
    OrganismType getType() const override { return OrganismType::ANT; }
};

class Doodlebug : public Organism {
public:
    Doodlebug(World* world, int x, int y) : Organism(world, x, y) {}
    void move() override;
    void breed() override;
    OrganismType getType() const override { return OrganismType::DOODLEBUG; }
    bool starve() override;
};

class World {
private:
    vector<vector<Organism*>> grid;
public:
    World();
    ~World();
    void display() const;
    void simulateStep();
    void placeOrganism(OrganismType type, int x, int y);
    Organism* getAt(int x, int y) const;
    void setAt(int x, int y, Organism* org);
    bool isInBounds(int x, int y) const { return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE; }
};

World::World() : grid(GRID_SIZE, vector<Organism*>(GRID_SIZE, nullptr)) {
    srand(time(NULL));
    // Initial placement of Doodlebugs
    for (int i = 0; i < 5; ++i) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (getAt(x, y) != nullptr);
        setAt(x, y, new Doodlebug(this, x, y));
    }
    // Initial placement of Ants
    for (int i = 0; i < 100; ++i) {
        int x, y;
        do {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        } while (getAt(x, y) != nullptr);
        setAt(x, y, new Ant(this, x, y));
    }
}

World::~World() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            delete grid[i][j];
        }
    }
}

void World::display() const {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == nullptr) cout << ".";
            else if (grid[i][j]->getType() == OrganismType::ANT) cout << "o";
            else cout << "X";
        }
        cout << "\n";
    }
    cout << "\n";
}

void World::simulateStep() {
    // Move phase
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr && !grid[i][j]->hasMoved()) {
                grid[i][j]->move();
            }
        }
    }
    // Clear moved flags
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->setMoved(false);
            }
        }
    }
    // Breed phase
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->breed();
            }
        }
    }
    // Starve phase
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == OrganismType::DOODLEBUG) {
                if (grid[i][j]->starve()) {
                    delete grid[i][j];
                    grid[i][j] = nullptr;
                }
            }
        }
    }
}

Organism* World::getAt(int x, int y) const {
    if (isInBounds(x, y)) return grid[x][y];
    return nullptr;
}

void World::setAt(int x, int y, Organism* org) {
    if (isInBounds(x, y)) {
        grid[x][y] = org;
    }
}


void Ant::breed() {
    if (getSteps() >= ANT_BREED) {
        array<pair<int, int>, 4> directions = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
        for (auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (world->isInBounds(newX, newY) && world->getAt(newX, newY) == nullptr) {
                world->setAt(newX, newY, new Ant(world, newX, newY));
                steps = 0; // Reset breeding timer
                break;
            }
        }
    }
}

pair<int, int> getRandomEmptyAdjacent(World* world, int x, int y) {
    array<pair<int, int>, 4> directions = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}}; // Right, Down, Left, Up
    random_device rd;
    mt19937 g(rd());
    shuffle(directions.begin(), directions.end(), g); // Randomize directions using shuffle

    for (auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        if (world->isInBounds(newX, newY) && world->getAt(newX, newY) == nullptr) {
            return {newX, newY};
        }
    }
    return {x, y}; // Return the original position if no empty adjacent found
}


void Ant::move() {
    auto [newX, newY] = getRandomEmptyAdjacent(world, x, y);
    if (newX != x || newY != y) {
        world->setAt(newX, newY, this);
        world->setAt(x, y, nullptr);
        x = newX;
        y = newY;
    }
    incrementSteps();
}

void Doodlebug::move() {
    bool ate = false;
    array<pair<int, int>, 4> directions = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}}; // Right, Down, Left, Up
    for (auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        if (world->isInBounds(newX, newY) && world->getAt(newX, newY) && world->getAt(newX, newY)->getType() == OrganismType::ANT) {
            delete world->getAt(newX, newY); // Eat the ant
            world->setAt(newX, newY, this);
            world->setAt(x, y, nullptr);
            x = newX;
            y = newY;
            steps = 0; // Reset starving timer after eating
            ate = true;
            break;
        }
    }
    if (!ate) { // If didn't eat, move like an Ant
        auto [newX, newY] = getRandomEmptyAdjacent(world, x, y);
        if (newX != x || newY != y) {
            world->setAt(newX, newY, this);
            world->setAt(x, y, nullptr);
            x = newX;
            y = newY;
        }
    }
}



void Doodlebug::breed() {
    if (getSteps() >= DOODLEBUG_BREED) {
        array<pair<int, int>, 4> directions = {{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};
        for (auto& dir : directions) {
            int newX = x + dir.first;
            int newY = y + dir.second;
            if (world->isInBounds(newX, newY) && world->getAt(newX, newY) == nullptr) {
                world->setAt(newX, newY, new Doodlebug(world, newX, newY));
                steps = 0; // Reset breeding timer
                break;
            }
        }
    }
}

bool Doodlebug::starve() {
    if (getSteps() >= DOODLEBUG_STARVE) {
        return true; // Doodlebug starves and dies
    }
    return false;
}
int main() {
    World world;
    char continueSim = 'y';
    while (continueSim == 'y') {
        world.display();
        world.simulateStep();
        cout << "Press 'y' to continue to the next step: ";
        cin >> continueSim;
    }
    return 0;
}

