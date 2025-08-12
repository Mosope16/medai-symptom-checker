#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

string to_lower(const string &str) {
    string lower = str;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

// Disease -> Symptoms list
map<string, vector<string>> diseaseDB = {
    {"Common Cold", {"sneezing", "runny nose", "sore throat", "cough", "fever"}},
    {"Influenza", {"fever", "chills", "muscle pain", "cough", "fatigue"}},
    {"Malaria", {"fever", "chills", "sweating", "headache", "nausea"}},
    {"Typhoid Fever", {"fever", "abdominal pain", "headache", "loss of appetite", "constipation"}},
    {"Pneumonia", {"cough", "fever", "chest pain", "difficulty breathing", "fatigue"}},
    {"COVID-19", {"fever", "dry cough", "tiredness", "loss of taste", "difficulty breathing"}},
    {"Tuberculosis", {"persistent cough", "blood in sputum", "night sweats", "fever", "weight loss"}},
    {"Asthma", {"shortness of breath", "chest tightness", "wheezing", "cough"}},
    {"Diabetes", {"frequent urination", "excessive thirst", "fatigue", "blurred vision", "slow wound healing"}},
    {"Hypertension", {"headache", "dizziness", "nosebleeds", "shortness of breath"}},
    {"Hepatitis B", {"fatigue", "nausea", "vomiting", "yellow skin", "abdominal pain"}},
    {"Dengue Fever", {"high fever", "rash", "joint pain", "muscle pain", "nausea"}},
    {"Chickenpox", {"rash", "itching", "fever", "loss of appetite", "headache"}},
    {"Meningitis", {"stiff neck", "fever", "headache", "nausea", "sensitivity to light"}},
    {"Measles", {"rash", "fever", "cough", "runny nose", "red eyes"}},
    {"Migraine", {"headache", "nausea", "sensitivity to light", "vomiting", "visual disturbances"}},
    {"UTI", {"painful urination", "frequent urination", "cloudy urine", "pelvic pain"}},
    {"Anemia", {"fatigue", "pale skin", "shortness of breath", "dizziness", "cold hands and feet"}},
    {"Appendicitis", {"abdominal pain", "nausea", "vomiting", "loss of appetite", "fever"}},
    {"Gastroenteritis", {"diarrhea", "vomiting", "abdominal cramps", "fever", "dehydration"}}
};

int main() {
    cout << "MedAI Offline Symptom Checker\n";
    cout << "Type 'exit' to quit anytime.\n";

    while (true) {
        cout << "\nEnter your symptoms (please add commas between symptoms): ";
        string input;
        getline(cin, input);

        if (to_lower(input) == "exit") {
            cout << "\nGoodbye!\n";
            break;
        }

        // Split user input into symptoms
        vector<string> userSymptoms;
        size_t pos = 0;
        string temp = input;
        while ((pos = temp.find(',')) != string::npos) {
            userSymptoms.push_back(to_lower(temp.substr(0, pos)));
            temp.erase(0, pos + 1);
        }
        userSymptoms.push_back(to_lower(temp));

        // Match & score diseases
        vector<pair<string, int>> results;

        for (auto &entry : diseaseDB) {
            int match = 0;
            for (auto &symptom : entry.second) {
                for (auto &userSymptom : userSymptoms) {
                    if (to_lower(symptom) == userSymptom) {
                        match++;
                    }
                }
            }
            if (match > 0) {
                results.push_back({entry.first, match});
            }
        }

        // Sort by match score (descending)
        sort(results.begin(), results.end(), [](auto &a, auto &b) {
            return b.second > a.second;
        });

        // Display results
        cout << "\nPossible Matches:\n";
        if (results.empty()) {
            cout << "No matching disease found. Try different symptoms.\n";
        } else {
            for (int i = 0; i < min(3, (int)results.size()); i++) {
                cout << i + 1 << ". " << results[i].first << " (match: " << results[i].second << ")\n";
            }
        }

        cout << "\nThis is not a diagnosis. Please consult a doctor.\n";
    }

    return 0;
}
