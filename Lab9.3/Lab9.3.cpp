#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

#pragma pack(push, 1)

struct Shop
{
    string shop_name;
    string item_name;
    double price_for_item; //у гривня
    int amount_of_items;   //наприклад 100 штук
};

#pragma pack(pop)

void Create(Shop* S, int N_start, const int N);
void Print(Shop* S, const int N);
void SaveToFile(Shop* S, const int N, const char* filenЬщame);
void LoadFromFile(Shop*& S, int& N, const char* filename);
void Sort(Shop* S, const int N, int SortType);
void Modify_string(Shop* S, const int N, int what_modify, string modify_to_string, int row);
void Modify_int(Shop* S, const int N, int what_modify, int modify_to_int, int row);
void print_info_item(Shop* S, const int N, string item_name);
void print_info_shop(Shop* S, const int N, string shop_name);
void push_back(Shop*& S, int N);
void del(Shop*& S, int N, int row_del);

int main()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість товарів: ";
    cin >> N;
    Shop* S = new Shop[N];

    int action;

    int SortType;

    int row_del;

    unsigned what_modify;
    string modify_to_string;
    int modify_to_int;
    int what_to_do;
    int row;

    int add;

    int action_case_5;

    string item_name, shop_name;

    char filename[100];

    do
    {
        cout << endl
            << endl;
        cout << "Виберіть дію: " << endl;
        cout << "1 - Введення даних з клавіатури" << endl;
        cout << "2 - Виведення інформації на екран" << endl;
        cout << "3 - Запис інформації у файл" << endl;
        cout << "4 - Зчитування даних із файлу" << endl;
        cout << "5 - Корегування списку з клавіатури" << endl;
        cout << "6 - Відсортувати список за назвою товару або за назвою магазину" << endl;
        cout << "7 - Пошук товару за його назвою" << endl;
        cout << "8 - Пошук товарів, які продаються в магазині" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: ";
        cin >> action;
        cout << endl
            << endl;

        switch (action)
        {
        case 1:
            Create(S, 0, N);
            break;
        case 2:
            Print(S, N);
            break;
        case 3:
            cin.get();
            cin.sync();

            cout << "Введіть назву файлу: ";
            cin.getline(filename, 99);
            SaveToFile(S, N, filename);
            break;
        case 4:
            cin.get();
            cin.sync();

            cout << "Введіть назву файлу: ";
            cin.getline(filename, 99);
            LoadFromFile(S, N, filename);
            break;
        case 5:
        {
            do
            {
                cout << "1 - Добавити" << endl;
                cout << "2 - Вилучити" << endl;
                cout << "3 - Редагувати" << endl;
                cout << "0 - Вихід" << endl;
                cout << "Введіть: ";
                cin >> action_case_5;

            } while (action_case_5 != 1 &&
                action_case_5 != 2 &&
                action_case_5 != 3 &&
                action_case_5 != 0);

            cout << endl;

            switch (action_case_5)
            {
            case 1:
                push_back(S, N++);
                break;
            case 2:
                cout << "Виберіть рядок. який потрібно видалити: ";
                cin >> row_del;

                del(S, N--, row_del - 1);
                break;
            case 3:
                do
                {
                    do
                    {
                        cout << "Що змінити?" << endl;
                        cout << "1 - Назва магазину" << endl;
                        cout << "2 - Назва товару" << endl;
                        cout << "3 - Вартість товару" << endl;
                        cout << "4 - Кількість товару" << endl;
                        cout << "Введіть: ";
                        cin >> what_modify;

                    } while (what_modify != 1 &&
                        what_modify != 2 &&
                        what_modify != 3 &&
                        what_modify != 4);

                    cout << endl;
                    switch (what_modify)
                    {
                    case 1:
                    case 2:
                        cout << "Введіть рядок: ";
                        cin >> row;
                        cout << endl;
                        cout << "На що замінити? " << endl;
                        cin.get();
                        cin.sync();

                        cout << "Введіть: ";
                        getline(cin, modify_to_string);

                        Modify_string(S, N, what_modify, modify_to_string, row);
                        break;
                    case 3:
                    case 4:
                        cout << "Введіть рядок: ";
                        cin >> row;
                        cout << endl;
                        cout << "На що замінити? " << endl;
                        cin.get();
                        cin.sync();

                        cout << "Введіть: ";
                        cin >> modify_to_int;

                        Modify_int(S, N, what_modify, modify_to_int, row);
                        break;
                    }

                    cout << "Бажаєте повторити корегування? (1 - Так, 2 - Ні)" << endl;
                    cout << "Введіть";
                    cin >> what_to_do;
                    cout << endl;
                } while (what_to_do != 2);
                break;
            }
            break;
        }
        case 6:
            cout << "За якими критеріями відсортувати?\n(1 - За назвою товару , 2 - За назвою магазину)" << endl;
            do
            {
                cout << "Введіть: ";
                cin >> SortType;

            } while (SortType != 1 && SortType != 2);

            Sort(S, N, SortType);
            break;
        case 7:
            cin.get();
            cin.sync();

            cout << "Введіть назву товару: ";
            getline(cin, item_name);

            print_info_item(S, N, item_name);
            break;
        case 8:
            cin.get();
            cin.sync();

            cout << "Введіть назву магазину: ";
            getline(cin, shop_name);

            print_info_shop(S, N, shop_name);
            break;
        case 0:
            return 0;
        default:
            cout << "Помилка!" << endl;
        }
    } while (action != 0);

    return 0;
}
void Create(Shop* S, int N_start, const int N)
{
    for (N_start; N_start < N; N_start++)
    {
        cout << "Товар №" << N_start + 1 << endl;
        cout << "Назву магазину: ";
        cin >> S[N_start].shop_name;
        cout << "Назву товару: ";
        cin >> S[N_start].item_name;
        cout << "Ціна за одиницю(грн.): ";
        cin >> S[N_start].price_for_item;
        cout << "Кількість(Шт., 1 упаковка = 20 кг.): ";
        cin >> S[N_start].amount_of_items;
        cout << endl
            << endl;
    }
}
void Print(Shop* S, const int N)
{
    cout << "==================================================================================" << endl;
    cout << "| № |  Назва магазину  |  Назва товару  |  Вартість товару  |  Кількість товару  |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << "|" << setw(2) << i + 1 << setw(2);
        cout << "|" << setw(10) << S[i].shop_name << setw(9);
        cout << "|" << setw(8) << S[i].item_name << setw(9);
        cout << "|" << setw(10) << S[i].price_for_item << setw(10);
        cout << "|" << setw(10) << S[i].amount_of_items << setw(11) << "|" << endl;
    }
    cout << "==================================================================================" << endl
        << endl;
}
void SaveToFile(Shop* S, const int N, const char* filename)
{
    ofstream fout(filename, ios::binary);

    fout.write((char*)&N, sizeof(N));

    for (int i = 0; i < N; i++)
        fout.write((char*)&S[i], sizeof(Shop));

    fout.close();
}
void LoadFromFile(Shop*& S, int& N, const char* filename)
{
    delete[] S;

    ifstream fin(filename, ios::binary);

    fin.read((char*)&N, sizeof(N));

    S = new Shop[N];

    for (int i = 0; i < N; i++)
        fin.read((char*)&S[i], sizeof(Shop));

    fin.close();
}
void Sort(Shop* S, const int N, int SortType)
{
    string Check, Check_Next;
    Shop tmp;

    for (int i0 = 0; i0 < N - 1; i0++)
    {
        for (int i1 = 0; i1 < N - i0 - 1; i1++)
        {
            switch (SortType)
            {
            case 1:
                Check = S[i1].item_name;
                Check_Next = S[i1 + 1].item_name;
                break;
            default:
                Check = S[i1].shop_name;
                Check_Next = S[i1 + 1].shop_name;
                break;
            }
            if (Check > Check_Next)
            {
                tmp = S[i1];
                S[i1] = S[i1 + 1];
                S[i1 + 1] = tmp;
            }
        }
    }
}
void Modify_string(Shop* S, const int N, int what_modify, string modify_to_string, int row)
{
    switch (what_modify)
    {
    case 1:
        S[row - 1].shop_name = modify_to_string;
        break;
    case 2:
        S[row - 1].item_name = modify_to_string;
        break;
    }
}
void Modify_int(Shop* S, const int N, int what_modify, int modify_to_int, int row)
{
    switch (what_modify)
    {
    case 3:
        S[row - 1].price_for_item = modify_to_int;
        break;
    case 4:
        S[row - 1].amount_of_items = modify_to_int;
        break;
    }
}
void print_info_item(Shop* S, const int N, string item_name)
{
    cout << "==================================================================================" << endl;
    cout << "| № |  Назва магазину  |  Назва товару  |  Вартість товару  |  Кількість товару  |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        if (S[i].item_name == item_name)
        {
            cout << "|" << setw(2) << i + 1 << setw(2);
            cout << "|" << setw(10) << S[i].shop_name << setw(9);
            cout << "|" << setw(8) << S[i].item_name << setw(9);
            cout << "|" << setw(10) << S[i].price_for_item << setw(10);
            cout << "|" << setw(10) << S[i].amount_of_items << setw(11) << "|" << endl;
        }
    }
    cout << "==================================================================================" << endl
        << endl;
}
void print_info_shop(Shop* S, const int N, string shop_name)
{
    cout << "==================================================================================" << endl;
    cout << "| № |  Назва магазину  |  Назва товару  |  Вартість товару  |  Кількість товару  |" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++)
    {
        if (S[i].shop_name == shop_name)
        {
            cout << "|" << setw(2) << i + 1 << setw(2);
            cout << "|" << setw(10) << S[i].shop_name << setw(9);
            cout << "|" << setw(8) << S[i].item_name << setw(9);
            cout << "|" << setw(10) << S[i].price_for_item << setw(10);
            cout << "|" << setw(10) << S[i].amount_of_items << setw(11) << "|" << endl;
        }
    }
    cout << "==================================================================================" << endl
        << endl;
}
void push_back(Shop*& S, int N)
{
    Shop* New_S = new Shop[N + 1];

    for (int i = 0; i < N; i++)
    {
        New_S[i].shop_name = S[i].shop_name;
        New_S[i].item_name = S[i].item_name;
        New_S[i].price_for_item = S[i].price_for_item;
        New_S[i].amount_of_items = S[i].amount_of_items;
    }

    cout << "Назву магазину: ";
    cin >> New_S[N].shop_name;
    cout << "Назву товару: ";
    cin >> New_S[N].item_name;
    cout << "Ціна за одиницю(грн.): ";
    cin >> New_S[N].price_for_item;
    cout << "Кількість(Шт., 1 упаковка = 20 кг.): ";
    cin >> New_S[N].amount_of_items;

    delete[] S;

    S = New_S;
}
void del(Shop*& S, int N, int row_del)
{
    int i = 0;

    Shop* New_S = new Shop[N - 1];

    for (i; i < row_del; i++)
    {
        New_S[i].shop_name = S[i].shop_name;
        New_S[i].item_name = S[i].item_name;
        New_S[i].price_for_item = S[i].price_for_item;
        New_S[i].amount_of_items = S[i].amount_of_items;
    }

    for (i; i < N - 1; i++)
    {
        New_S[i].shop_name = S[i + 1].shop_name;
        New_S[i].item_name = S[i + 1].item_name;
        New_S[i].price_for_item = S[i + 1].price_for_item;
        New_S[i].amount_of_items = S[i + 1].amount_of_items;
    }

    delete[] S;

    S = New_S;
}