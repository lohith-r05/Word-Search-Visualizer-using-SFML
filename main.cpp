#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;

const int TILE_SIZE = 50;
const int DIRECTIONS[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; 


bool readInput(const string& filename, vector<vector<char>>& grid, vector<string>& words) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string gridLine;
    if (!getline(file, gridLine)) {
        cerr << "Error: Could not read grid line" << endl;
        return false;
    }

    int grid_size = sqrt(gridLine.size());
    grid.resize(grid_size, vector<char>(grid_size));
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            if (i * grid_size + j < gridLine.size()) grid[i][j] = toupper(gridLine[i * grid_size + j]);
            else grid[i][j] = ' ';
        }
    }

    string wordsLine;
    if (!getline(file, wordsLine)) {
        cerr << "Error: Could not read words line" << endl;
        return false;
    }

    stringstream ss(wordsLine);
    string word;
    while (getline(ss, word, ',')) {
        for (char& c : word) c = toupper(c); 
        words.push_back(word);
    }
    file.close();
    return true;
}

bool searchWord(int i, int j, int di, int dj, const vector<vector<char>>& grid, 
               const string& word, int index, vector<pair<int, int>>& path) {
    if (index == word.size()) return true;
    if (i < 0 || j < 0 || i >= grid.size() || j >= grid.size() || 
        grid[i][j] != word[index]) return false;

    path.push_back({i, j});
    bool found = searchWord(i + di, j + dj, di, dj, grid, word, index + 1, path);
    if (!found) path.pop_back();
    return found;
}

vector<vector<pair<int, int>>> findWords(const vector<vector<char>>& grid, 
                                       const vector<string>& words) {
    vector<vector<pair<int, int>>> wordPaths(words.size());

    for (int w = 0; w < words.size(); ++w) {
        const string& word = words[w];
        bool found = false;

        for (int i = 0; i < grid.size() && !found; ++i) {
            for (int j = 0; j < grid.size() && !found; ++j) {
                if (toupper(grid[i][j]) == word[0]) {
                    for (const auto& dir : DIRECTIONS) {
                        vector<pair<int, int>> path;
                        if (searchWord(i, j, dir[0], dir[1], grid, word, 0, path)) {
                            wordPaths[w] = path;
                            found = true;
                            break;
                        }
                    }
                }
            }
        }
    }

    return wordPaths;
}

int main() {
    vector<vector<char>> grid;
    vector<string> words;

    if (!readInput("inputs/input3.txt", grid, words)) {
        system("pause");
        return -1;
    }

    vector<vector<pair<int, int>>> wordPaths = findWords(grid, words);

    cout << "Found Words:" << endl;
    for (int w = 0; w < words.size(); ++w) 
        cout << words[w] << " (" << (wordPaths[w].empty() ? "No" : "Yes") << ")" << endl;

    sf::RenderWindow window(sf::VideoMode(grid.size() * TILE_SIZE, 
                           grid.size() * TILE_SIZE + 50), "Word Search Solver");
    
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) cerr << "Error: Could not load font. Using default." << endl;

    bool windowClosed = false;
    while (!windowClosed) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) windowClosed = true;
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid.size(); ++j) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE - 2, TILE_SIZE - 2));
                tile.setPosition(j * TILE_SIZE + 1, i * TILE_SIZE + 1);
                tile.setFillColor(sf::Color::White);
                tile.setOutlineThickness(1);
                tile.setOutlineColor(sf::Color(200, 200, 200));
                window.draw(tile);

                sf::Text letter;
                letter.setFont(font);
                letter.setString(string(1, grid[i][j]));
                letter.setCharacterSize(24);
                letter.setFillColor(sf::Color::Black);
                letter.setPosition(j * TILE_SIZE + 15, i * TILE_SIZE + 10);
                window.draw(letter);
            }
        }

        // Highlight found words
        vector<sf::Color> colors = {sf::Color::Green, sf::Color::Blue, sf::Color::Red, 
                                   sf::Color::Magenta, sf::Color::Cyan};
        
        for (int w = 0; w < wordPaths.size(); ++w) {
            if (!wordPaths[w].empty()) {
                for (const auto& pos : wordPaths[w]) {
                    sf::RectangleShape highlight(sf::Vector2f(TILE_SIZE - 4, TILE_SIZE - 4));
                    highlight.setPosition(pos.second * TILE_SIZE + 2, pos.first * TILE_SIZE + 2);
                    highlight.setFillColor(sf::Color(colors[w % colors.size()].r, 
                                                  colors[w % colors.size()].g, 
                                                  colors[w % colors.size()].b, 150));
                    window.draw(highlight);
                }
            }
        }

        window.display();

        if (windowClosed) {
            sf::sleep(sf::seconds(1));  // Show final frame for 1 second
            break;
        }
    }

    system("pause");
    return 0;
}
