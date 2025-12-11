#include <iostream>
#include <set>
#include <bitset>
#include <assert.h>
#define int long long
using std::cout;
using std::endl;

const int H = 64;
typedef std::bitset<H> bs;

class set
{
private:
    int *data = nullptr;
    bool *full = nullptr;
    bs *bitmap = nullptr;
    int a1, b1;
    int table_size = 0;
    int set_size = 0;

    bool is_prime(int n)
    {
        if (n == 2 || n == 3)
            return true;

        if (n == 1 || n % 2 == 0)
            return false;

        for (int i = 3; i * i <= n; i += 2)
            if (n % i == 0)
                return false;

        return true;
    }

    int next_prime(int n)
    {
        if (n % 2 == 0)
            ++n;

        for (; !is_prime(n); n += 2)
            ;

        return n;
    }

    void rehash(bool __first_time__ = false)
    {
        int *old_data = data;
        bool *old_full = full;
        bs *old_bitmap = bitmap;
        int old_data_size = __first_time__ ? 0 : table_size;

        bool success = false;

        while (!success)
        {
            table_size = __first_time__ ? 37 : next_prime(table_size * 2);
            data = new int[(table_size)];
            full = new bool[(table_size)];
            bitmap = new bs[(table_size)];
            for (int i = 0; i < (table_size); i++)
            {
                full[i] = false;
                bitmap[i] = 0;
                data[i] = 0;
            }

            a1 = std::abs(std::rand()) % (table_size - 1) + 1;
            b1 = std::abs(std::rand()) % (table_size);

            success = true;
            if (!__first_time__)
                for (int i = 0; i < old_data_size; i++)
                    if (old_full[i])
                    {
                        if (__insert__(old_data[i]) == 2)
                        {
                            delete[] data;
                            delete[] full;
                            delete[] bitmap;
                            success = false;
                            break;
                        }
                    }
        }

        if (!__first_time__)
        {
            delete[] old_data;
            delete[] old_full;
            delete[] old_bitmap;
        }
    }

    int compute_hash(int key)
    {
        return (((long long)(key * a1) + b1) % table_size + table_size) % table_size;
    }

    int __insert__(int key)
    {
        if (count(key))
            return 0;

        int index = compute_hash(key);

        if (bitmap[index].count() == H)
            return 2;

        int j = -1;

        for (int i = index, _c = 0; _c < table_size; i = (i + 1) % table_size, _c++)
        {
            if (!full[i])
            {
                j = i;
                break;
            }
        }

        if (j == -1)
            return 2;

        while ((j - index + table_size) % table_size >= H)
        {
            int old_j = j;
            for (int i = (j - 1 + table_size) % table_size, _c = 0; _c < H - 1; i = (i - 1 + table_size) % table_size, _c++)
            {
                int hash = compute_hash(data[i]);
                if ((j - hash + table_size) % table_size < H)
                {
                    bitmap[hash][(j - hash + table_size) % table_size] = 1;
                    bitmap[hash][(i - hash + table_size) % table_size] = 0;
                    full[j] = true;
                    full[i] = false;
                    data[j] = data[i];
                    j = i;
                    break;
                }
            }
            if (j == old_j)
                return 2;
        }

        data[j] = key;
        full[j] = true;
        bitmap[index][(j - index + table_size) % table_size] = 1;
        return 1;
    }

public:
    set()
    {
        rehash(true);
    }

    set(const set &) = delete;
    set &operator=(const set &) = delete;

    int count(int key)
    {
        auto index = compute_hash(key);
        for (int i = index; i != (index + H) % table_size; i = (i + 1) % table_size)
        {
            if (full[i] && data[i] == key)
                return 1;
        }
        return 0;
    }

    bool erase(int key)
    {
        auto index = compute_hash(key);
        for (int i = index, h_index = 0; h_index < H; i = (i + 1) % table_size, h_index++)
        {
            if (full[i] && data[i] == key)
            {
                full[i] = false;
                bitmap[index][h_index] = 0;
                data[i] = 0;
                set_size--;
                return true;
            }
        }
        return false;
    }

    bool insert(int key)
    {
        auto a = __insert__(key);
        if (a == 2)
        {
            rehash();
            return insert(key);
        }

        if (a)
            set_size++;
        return a;
    }

    int size()
    {
        return set_size;
    }

    ~set()
    {
        delete[] data;
        delete[] full;
        delete[] bitmap;
    }
};

#pragma region Tests
void stress_test(set &mySet, int num_operations, int max_key_value)
{
    cout << "## 🏋️ Stress Test (Total Operations: " << num_operations << ")" << endl;

    // Use a standard library set to track the expected state for verification
    std::set<int> oracle_set;

    // Ensure the random number generator is ready
    srand(time(0));

    int insert_count = 0;
    int erase_count = 0;
    int expected_size = 0;

    for (int i = 0; i < num_operations; ++i)
    {
        // Generate a random key within the specified range
        int key = rand() % max_key_value;

        // Choose a random operation (0: Insert, 1: Erase, 2: Check Integrity)
        int operation = rand() % 3;

        if (operation == 0 || (operation == 2 && oracle_set.find(key) == oracle_set.end()))
        {
            // --- INSERTION TEST ---
            bool set_inserted = mySet.insert(key);
            bool oracle_inserted = oracle_set.insert(key).second;
            assert(set_inserted == oracle_inserted);
            if (set_inserted != oracle_inserted)
            {
                cout << "❌ STRESS FAIL: Insert Mismatch for key " << key << endl;
                return;
            }
            if (set_inserted)
            {
                insert_count++;
                expected_size++;
            }
        }
        else if (operation == 1 || (operation == 2 && oracle_set.find(key) != oracle_set.end()))
        {
            // --- ERASURE TEST ---
            bool set_erased = mySet.erase(key);
            bool oracle_erased = (oracle_set.erase(key) == 1);
            assert(set_erased == oracle_erased);
            if (set_erased != oracle_erased)
            {
                cout << "❌ STRESS FAIL: Erase Mismatch for key " << key << endl;
                return;
            }
            if (set_erased)
            {
                erase_count++;
                expected_size--;
            }
        }
    }

    // --- FINAL INTEGRITY CHECK ---
    cout << "\n--- Final Integrity Check ---" << endl;
    bool integrity_ok = true;

    // 1. Check size
    if (mySet.size() != expected_size)
    {
        cout << "❌ STRESS FAIL: Size Mismatch. Custom size: " << mySet.size() << ", Expected: " << expected_size << endl;
        integrity_ok = false;
    }

    // 2. Check all elements in the oracle set are present in the custom set
    int missing_count = 0;
    for (int key : oracle_set)
    {
        if (!mySet.count(key))
        {
            // Only print a few missing keys to avoid flooding the output
            if (missing_count < 5)
            {
                cout << "❌ STRESS FAIL: Key " << key << " is missing." << endl;
            }
            missing_count++;
        }
    }

    if (missing_count > 0)
    {
        cout << "❌ STRESS FAIL: Total " << missing_count << " keys missing from the custom set." << endl;
        integrity_ok = false;
    }

    if (integrity_ok)
    {
        cout << "✅ STRESS PASS: All " << num_operations << " operations completed successfully." << endl;
        cout << "   Final Size: " << mySet.size() << endl;
        cout << "   Insertions: " << insert_count << ", Erasures: " << erase_count << endl;
    }
    cout << "---" << endl;
}

// Note : AI has been used only to write the tests.
signed main()
{
    // Initialize random seed for rand() used in hashing
    srand(time(0));

    set stressSet;
    const int total_operations = 100000; // Run 100,000 random operations
    const int key_range = 50000;         // Keys will be between 0 and 49999

    // The current capacity will be 2 * nextPrime(8 * 2^k)
    // Running 100,000 operations will force multiple rehashes under load.

    stress_test(stressSet, total_operations, key_range);

    cout << "\n✅ Testing complete. Destructor will now be called." << endl;

    cout << "🧪 Testing the custom 'set' (Hopscotch Hashing) implementation.\n"
         << endl;

    set mySet;

    // --- 1. Insertion Test ---
    cout << "## ➕ Insertion Test" << endl;
    int numbers_to_insert[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 15, 25, 35, 45, 55};
    int successful_inserts = 0;

    for (int num : numbers_to_insert)
    {
        if (mySet.insert(num))
        {
            cout << "Inserted: " << num << endl;
            successful_inserts++;
        }
        else
        {
            cout << "Failed to insert (or already exists): " << num << endl;
        }
    }
    cout << "\nTotal elements inserted: **" << mySet.size() << "** (Expected: " << successful_inserts << ")" << endl;
    cout << "---" << endl;

    // --- 2. Count/Existence Test ---
    cout << "## 🔎 Count/Existence Test" << endl;

    // Check for existing elements
    int check1 = 30;
    cout << "Checking for " << check1 << ": " << (mySet.count(check1) ? "✅ Found" : "❌ Not Found") << endl;

    int check2 = 100;
    cout << "Checking for " << check2 << ": " << (mySet.count(check2) ? "✅ Found" : "❌ Not Found") << endl;

    // Check for non-existing element
    int check3 = 99;
    cout << "Checking for " << check3 << " (non-existent): " << (mySet.count(check3) ? "❌ Found" : "✅ Not Found") << endl;
    cout << "---" << endl;

    // --- 3. Duplicate Insertion Test ---
    cout << "## 🔁 Duplicate Insertion Test" << endl;
    int duplicate_key = 40;
    bool inserted_duplicate = mySet.insert(duplicate_key);
    cout << "Attempting to insert " << duplicate_key << " again. Success: " << (inserted_duplicate ? "❌ YES (Error)" : "✅ NO (Correct)") << endl;
    cout << "Set size after duplicate attempt: " << mySet.size() << endl;
    cout << "---" << endl;

    // --- 4. Erasure Test ---
    cout << "## 🗑️ Erasure Test" << endl;
    int key_to_erase = 50;
    int size_before_erase = mySet.size();

    bool erased = mySet.erase(key_to_erase);
    cout << "Attempting to erase " << key_to_erase << ". Success: " << (erased ? "✅ YES" : "❌ NO") << endl;
    cout << "Set size: " << mySet.size() << " (Expected: " << (size_before_erase - (erased ? 1 : 0)) << ")" << endl;

    // Verify erasure
    cout << "Checking for " << key_to_erase << " after erasure: " << (mySet.count(key_to_erase) ? "❌ Found" : "✅ Not Found") << endl;
    cout << "---" << endl;

    // --- 5. Erase Non-existent Test ---
    int non_existent_key = 50; // Use the key we just erased
    bool erased_non_existent = mySet.erase(non_existent_key);
    cout << "Attempting to erase " << non_existent_key << " (non-existent). Success: " << (erased_non_existent ? "❌ YES (Error)" : "✅ NO (Correct)") << endl;
    cout << "Set size: " << mySet.size() << endl;
    cout << "---" << endl;

    // --- 6. Large-Scale Test (to potentially trigger rehash) ---
    // The initial table_size is 17, array size is 34.
    // Let's insert more to trigger the rehash logic.
    cout << "## 📈 Large-Scale Test (Rehash Potential)" << endl;
    for (int i = 200; i < 250; ++i)
    { // Insert 50 more elements
        mySet.insert(i);
    }
    cout << "Inserted 50 more elements (200 to 249)." << endl;
    cout << "Final set size: **" << mySet.size() << "**" << endl;
    cout << "Checking a newly inserted element (235): " << (mySet.count(235) ? "✅ Found" : "❌ Not Found") << endl;
    cout << "---" << endl;

    cout << "\n✅ Testing complete. Destructor will now be called." << endl;

    return 0;
}
#pragma endregion