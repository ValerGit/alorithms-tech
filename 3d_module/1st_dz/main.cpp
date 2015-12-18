/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической
 *  хеш­таблицы с открытой адресацией. Хранимые строки непустые и состоят
 * из строчных латинских букв. Начальный размер таблицы должен быть равным 8­ми.
 * Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент
 * заполнения таблицы достигает 3/4.
 * ​Для разрешения коллизий используйте квадратичное пробирование.
 * i­ая проба g(k, i)=g(k, i­1) + i (mod m). m ­ степень двойки.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t defaultTableSize = 8;
const size_t growFactor = 2;
const float maxFilling = 0.75;
const string deleted = "!";

int Hash( const string& data, int tableSize ) {
    int hash = 0;
    for ( int i = 0; i < (int) data.length(); ++i ) {
        hash = ( 127 * hash + data[i] ) % tableSize;
    }
    return hash;
}

template<class T>
class HashTable {
public:
    HashTable();
    ~HashTable();

    bool Has( const T &obj ) const;
    bool Add( const T &obj );
    bool Delete( const T &obj );

private:
    void grow();
    int quadroProbing( int posit, int iter ) const;

    vector<T> arr;
    size_t keyCount;
    size_t deletedCount;
};

template<class T>
HashTable<T>::HashTable() {
    arr.resize( defaultTableSize, "" );
    keyCount = 0;
    deletedCount = 0;
}

template<class T>
HashTable<T>::~HashTable() {
    arr.clear();
}

template<class T>
void HashTable<T>::grow() {
    vector<T> temp = arr;
    arr.clear();
    arr.resize( temp.size() * growFactor, "" );

    keyCount = 0;
    deletedCount = 0;
    for ( int i = 0; i < (int) temp.size(); ++i ) {
        if ( temp[i] != deleted && temp[i] != "" ) {
            int inPos = Hash ( temp[i], arr.size() );
            int posHash = 0;

            for ( int j = 0; j < (int) arr.size(); ++j ) {
                posHash = quadroProbing( inPos, j );
                if (arr[posHash] == "") {
                    arr[posHash] = temp[i];
                    ++keyCount;
                    break;
                }
            }
        }
    }
    temp.clear();
}

template<class T>
bool HashTable<T>::Has( const T &obj ) const{
    int initPos = Hash (obj, arr.size());
    int posHash = 0;

    for (int i = 0; i < (int) arr.size(); ++i) {
        posHash = quadroProbing( initPos, i );
        if (arr[posHash] == "") return false;
        else if (arr[posHash] == obj) return true;
    }
    return false;
}

template<class T>
bool HashTable<T>::Add(const T &obj) {
    if(Has(obj)) return false;

    if ( (( keyCount + 1 ) > (size_t) (( arr.size() * maxFilling )))
            || ( deletedCount > (arr.size() / 2)) ) grow();

    int inPos = Hash (obj, arr.size());
    int posHash = 0;

    for (int i = 0; i < (int) arr.size(); ++i) {
        posHash = quadroProbing( inPos, i );
        if (arr[posHash] == "" || arr[posHash] == deleted) {
            arr[posHash] = obj;
            if( arr[posHash] == deleted) --deletedCount;
            ++ keyCount;
            return true;
        }
    }
}

template<class T>
bool HashTable<T>::Delete( const T &obj ) {
    if( !Has(obj) ) return false;

    int initPos = Hash( obj, arr.size() );
    int posHash = 0;

    for ( int i = 0; i < (int) arr.size(); ++i ) {
        posHash = quadroProbing( initPos, i );
        if (arr[posHash] == obj) {
            arr[posHash] = deleted;
            --keyCount;
            ++ deletedCount;
            return true;
        }
    }
}

template<class T>
int HashTable<T>::quadroProbing( int posit, int iter ) const {
    return (int) (( posit + (( iter * (iter + 1) / 2 ))) % arr.size());
}

int main() {
    char operation = 0;
    string word;
    HashTable<string>* table = new HashTable<string>;

    while (cin >> operation >> word) {
        switch ( operation ) {
            case '+': {
                cout << (table->Add(word) ? "OK" : "FAIL") << endl;
                break;
            }
            case '-': {
                cout << (table->Delete(word) ? "OK" : "FAIL") << endl;
                break;
            }
            case '?': {
                cout << (table->Has(word) ? "OK" : "FAIL") << endl;
                break;
            }
        }
    }
    delete table;
    return 0;
}

