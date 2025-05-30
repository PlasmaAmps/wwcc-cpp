#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;

// Struct to hold a single recipe
struct Recipe {
    string name;
    vector<string> ingredients;
    vector<string> steps;
};

// Function declarations
void addRecipe(vector<Recipe>& recipes);
void displayRecipes(const vector<Recipe>& recipes);
void searchRecipes(const vector<Recipe>& recipes);
void removeRecipe(vector<Recipe>& recipes);
void showStatistics(const vector<Recipe>& recipes);
int getValidatedInt(const string& prompt, int min = 1);

int main() {
    vector<Recipe> recipes;
    int choice;

    while (true) {
        cout << "\nDYNAMIC RECIPE MANAGER\n---------------------\n";
        cout << "1. Add Recipe\n";
        cout << "2. Display All Recipes\n";
        cout << "3. Search Recipes\n";
        cout << "4. Remove Recipe\n";
        cout << "5. Show Statistics\n";
        cout << "6. Exit\n";
        cout << "\nEnter choice: ";

        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        cin.ignore(); // clear newline

        switch (choice) {
            case 1: addRecipe(recipes); break;
            case 2: displayRecipes(recipes); break;
            case 3: searchRecipes(recipes); break;
            case 4: removeRecipe(recipes); break;
            case 5: showStatistics(recipes); break;
            case 6: cout << "Goodbye!\n"; return 0;
        }
    }
}

void addRecipe(vector<Recipe>& recipes) {
    Recipe r;
    cout << "Enter recipe name: ";
    getline(cin, r.name);

    int numIngredients = getValidatedInt("How many ingredients?");
    for (int i = 1; i <= numIngredients; ++i) {
        string ingredient;
        cout << "Enter ingredient " << i << ": ";
        getline(cin, ingredient);
        r.ingredients.push_back(ingredient);
    }

    int numSteps = getValidatedInt("How many steps?");
    for (int i = 1; i <= numSteps; ++i) {
        string step;
        cout << "Enter step " << i << ": ";
        getline(cin, step);
        r.steps.push_back(step);
    }

    recipes.push_back(r);
    cout << "\nRecipe added successfully!\n";
}

void displayRecipes(const vector<Recipe>& recipes) {
    if (recipes.empty()) {
        cout << "\nNo recipes to display.\n";
        return;
    }

    cout << "\nALL RECIPES\n-----------\n";
    for (size_t i = 0; i < recipes.size(); ++i) {
        cout << "Recipe #" << i + 1 << ": " << recipes[i].name << "\n";
        cout << "Ingredients:\n";
        for (const auto& ing : recipes[i].ingredients)
            cout << "  - " << ing << "\n";

        cout << "Steps:\n";
        for (size_t j = 0; j < recipes[i].steps.size(); ++j)
            cout << "  " << j + 1 << ". " << recipes[i].steps[j] << "\n";
        cout << "-----------\n";
    }
}

void searchRecipes(const vector<Recipe>& recipes) {
    if (recipes.empty()) {
        cout << "\nNo recipes to search.\n";
        return;
    }

    string term;
    cout << "Enter search term (name or ingredient): ";
    getline(cin, term);

    bool found = false;
    cout << "\nSEARCH RESULTS\n--------------\n";
    for (const auto& recipe : recipes) {
        if (recipe.name.find(term) != string::npos) {
            cout << "Match found: " << recipe.name << " (by name)\n";
            found = true;
        } else {
            for (const auto& ing : recipe.ingredients) {
                if (ing.find(term) != string::npos) {
                    cout << "Match found: " << recipe.name << " (ingredient: " << ing << ")\n";
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found)
        cout << "No matching recipes found.\n";
}

void removeRecipe(vector<Recipe>& recipes) {
    if (recipes.empty()) {
        cout << "\nNo recipes to remove.\n";
        return;
    }

    displayRecipes(recipes);
    int index = getValidatedInt("Enter recipe number to remove", 1);
    if (index < 1 || index > static_cast<int>(recipes.size())) {
        cout << "Invalid recipe number.\n";
        return;
    }

    recipes.erase(recipes.begin() + (index - 1));
    cout << "Recipe removed successfully.\n";
}

void showStatistics(const vector<Recipe>& recipes) {
    cout << "\nCOLLECTION STATISTICS\n--------------------\n";
    cout << "Total recipes: " << recipes.size() << "\n";

    if (!recipes.empty()) {
        int totalIngredients = 0, totalSteps = 0;
        for (const auto& r : recipes) {
            totalIngredients += r.ingredients.size();
            totalSteps += r.steps.size();
        }

        double avgIngredients = static_cast<double>(totalIngredients) / recipes.size();
        double avgSteps = static_cast<double>(totalSteps) / recipes.size();

        cout << fixed << setprecision(1);
        cout << "Average ingredients per recipe: " << avgIngredients << "\n";
        cout << "Average steps per recipe: " << avgSteps << "\n";
    }
}

int getValidatedInt(const string& prompt, int min) {
    int value;
    while (true) {
        cout << prompt << " ";
        cin >> value;
        if (!cin.fail() && value >= min) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number >= " << min << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
