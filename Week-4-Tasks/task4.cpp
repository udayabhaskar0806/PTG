#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <set>

using namespace std;

// Define the Control struct
struct Control {
    int id;
    string type;
    string state;

    void print() const {
        cout << "ID: " << id << ", Type: " << type << ", State: " << state << endl;
    }

    // For sorting controls by id
    bool operator<(const Control& other) const {
        return id < other.id;
    }
};

int main() {
    // Sample lists of controls
    vector<Control> controls1 = {
        {10, "button", "visible"}, {2, "slider", "invisible"},
        {5, "button", "disabled"}, {8, "slider", "visible"}
    };

    vector<Control> controls2 = {
        {3, "button", "visible"}, {7, "slider", "disabled"},
        {5, "button", "visible"}, {12, "slider", "invisible"}
    };

    // Step 1: Sorting the controls by their ID using std::sort
    sort(controls1.begin(), controls1.end());
    sort(controls2.begin(), controls2.end());

    // Display sorted lists
    cout << "Sorted controls1:" << endl;
    for (const auto& c : controls1) c.print();
    cout << "\nSorted controls2:" << endl;
    for (const auto& c : controls2) c.print();

    // Step 2: Using std::stable_sort to maintain relative order for equal IDs
    stable_sort(controls1.begin(), controls1.end(), [](const Control& a, const Control& b) {
        return a.id < b.id;
    });

    cout << "\nStable sorted controls1 (maintaining relative order for equal IDs):" << endl;
    for (const auto& c : controls1) c.print();

    // Step 3: Binary Search using std::lower_bound and std::upper_bound
    auto it = lower_bound(controls1.begin(), controls1.end(), Control{5, "", ""});
    if (it != controls1.end() && it->id == 5) {
        cout << "\nFound Control with ID 5 using lower_bound: ";
        it->print();
    } else {
        cout << "\nControl with ID 5 not found using lower_bound." << endl;
    }

    it = upper_bound(controls1.begin(), controls1.end(), Control{5, "", ""});
    if (it != controls1.end()) {
        cout << "\nFound the first Control with ID greater than 5 using upper_bound: ";
        it->print();
    } else {
        cout << "\nNo Control with ID greater than 5 using upper_bound." << endl;
    }

    // Step 4: Merging two sorted lists using std::merge
    vector<Control> mergedControls(controls1.size() + controls2.size());
    merge(controls1.begin(), controls1.end(), controls2.begin(), controls2.end(), mergedControls.begin());

    cout << "\nMerged controls (using std::merge):" << endl;
    for (const auto& c : mergedControls) c.print();

    // Step 5: Using std::inplace_merge to merge two segments within the same vector
    vector<Control> controlsToMerge = { {2, "slider", "invisible"}, {5, "button", "disabled"},
                                        {8, "slider", "visible"} };
    vector<Control> controlsToMerge2 = { {3, "button", "visible"}, {7, "slider", "disabled"},
                                         {5, "button", "visible"} };

    // Sort both sub-vectors first
    sort(controlsToMerge.begin(), controlsToMerge.end());
    sort(controlsToMerge2.begin(), controlsToMerge2.end());

    // Perform inplace_merge
    controlsToMerge.insert(controlsToMerge.end(), controlsToMerge2.begin(), controlsToMerge2.end());
    inplace_merge(controlsToMerge.begin(), controlsToMerge.begin() + controlsToMerge.size() / 2, controlsToMerge.end());

    cout << "\nAfter inplace_merge (merged sorted lists within the same vector):" << endl;
    for (const auto& c : controlsToMerge) c.print();

    // Step 6: Set operations: std::set_union and std::set_intersection
    set<Control> set1(controls1.begin(), controls1.end());
    set<Control> set2(controls2.begin(), controls2.end());

    vector<Control> unionResult;
    vector<Control> intersectionResult;

    // Union of set1 and set2
    set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(unionResult));

    // Intersection of set1 and set2
    set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(intersectionResult));

    cout << "\nUnion of controls (unique controls from both lists):" << endl;
    for (const auto& c : unionResult) c.print();

    cout << "\nIntersection of controls (common controls between both lists):" << endl;
    for (const auto& c : intersectionResult) c.print();

    return 0;
}
