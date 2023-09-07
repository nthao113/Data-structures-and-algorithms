
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <string>

#define MAX 50
using namespace std;

struct buyBook
{
    unsigned int BookID;
    string bookTitle;
    unsigned long bookPrice;
    unsigned long quantity;
};
struct Book
{
    unsigned int BookID;
    string bookTitle;
    unsigned long bookPrice;
    unsigned long originalBookPrice;
    unsigned int booksRemaining;
    unsigned int booksSold;
    unsigned int totalBooks;
};
// Tao danh sach kho hang su dung cau truc Doubly Lnked List
struct Node
{
    Book data;
    Node *next;
    Node *prev;
};
struct List
{
private:
    Node *head = NULL;
    Node *tail = NULL;
    int len = 0;

public:
    // Kiem tra co phan tu nao khong
    int isEmptyList() { return len == 0; }

    // Xuat so phan tu
    int getlen() { return len; }

    // tra ve phan co so thu tu la p
    Node *getItem(int &p)
    {
        if (head == NULL)
            return NULL;
        while (p <= 0 || p > len)
        {
            cout << " >> Enter the appropriate location: ";
            cin >> p;
        };
        Node *q = head;
        for (int i = 1; i < p; i++)
        {
            q = q->next;
        };
        return q;
    }

    // Them vao vi tri dau
    void addFirst(Book s)
    {
        Node *p = new Node();
        check(s);
        p->data = s;
        p->prev = NULL;
        p->next = head;
        if (head != NULL)
        {
            head->prev = p;
        }
        else
        {
            tail = p;
        };
        head = p;
        len++;
    }

    // them vao vi tri cuoi
    void addLast(Book s)
    {
        Node *p = new Node();
        check(s);
        p->data = s;
        p->next = NULL;
        p->prev = tail;
        if (tail != NULL)
        {
            tail->next = p;
        }
        else
        {
            head = p;
        };
        tail = p;
        len++;
    }

    // Them vao vi tri bat ky
    int addItem(Node *p, Book s)
    {
        if (p == NULL || p->prev == NULL)
        {
            addFirst(s);
            return 0;
        };
        Node *q = new Node();
        check(s);
        q->data = s;
        q->next = p;
        q->prev = p->prev;
        q->next->prev = q;
        q->prev->next = q;
        len++;
        return 1;
    }

    // xoa phan tu dau tien
    void removeFirst()
    {
        if (head != NULL)
        {
            Node *q = head;
            head = q->next;
            if (q->next != NULL)
            {
                q->next->prev = NULL;
            }
            else
            {
                tail = NULL;
            };
            delete q;
            len--;
        }
    }

    // xoa phan tu cuoi cung
    void removeLast()
    {
        if (tail != NULL)
        {
            Node *p = tail;
            tail = p->prev;
            if (p->prev != NULL)
            {
                p->prev->next = NULL;
            }
            else
            {
                head = NULL;
            };
            delete p;
            len--;
        }
    }

    // Xoa vi tri bat ky
    int removeItem(Node *p)
    {
        if (p != NULL)
        {
            if (p->prev == NULL)
            {
                removeFirst();
                return 0;
            };
            if (p->next == NULL)
            {
                removeLast();
                return 0;
            };
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            len--;
            return 1;
        }
    }

    // doi du lieu hai phan tu bat ki
    // Luu y khi su dung, chua hoan thien cho tat ca truong hop
    void swap(Node *q, Node *p)
    {
        Book a = q->data;
        q->data = p->data;
        p->data = a;
    }

    // Sap xep danh sanh tang dan
    void sortList()
    {
        if (head != NULL)
        {
            Node *min;
            Node *q = head;
            Node *p;
            while (q->next != NULL)
            {
                min = q;
                p = q->next;
                while (p != NULL)
                {
                    if (min->data.BookID > p->data.BookID)
                        min = p;
                    p = p->next;
                }
                swap(min, q);
                q = q->next;
            };
        }
        printList();
    }

    // tim kiem sach
    void searchItem(string t)
    {
        Node *q = head;
        int i = 1;
        while (q != NULL)
        {
            if (q->data.bookTitle == t)
            {
                printItem(i);
            };
            q = q->next;
            i++;
        }
    }
    int searchItem(unsigned int ms)
    {
        Node *q = head;
        int i = 1;
        while (q != NULL)
        {
            if (q->data.BookID == ms)
            {
                printItem(i);
                return 1;
            };
            q = q->next;
            i++;
        }
        return 0;
    }
    int searchItem(buyBook &sm, Node *&s)
    {
        s = head;
        int i = 1;
        while (s != NULL)
        {
            if (s->data.BookID == sm.BookID)
            {
                printItem(i);
                sm.bookTitle = s->data.bookTitle;
                sm.bookPrice = s->data.bookPrice;
                return 1;
            };
            s = s->next;
            i++;
        }
        return 0;
    }

    // Chinh sua
    int changeItem(unsigned int ms)
    {
        Node *q = head;
        int i = 1;
        while (q != NULL)
        {
            int change;
            if (q->data.BookID == ms)
            {
                printItem(i);
                cout << " << Re-enter book information." << endl;
                for (int j = 0; j < 85; j++)
                    cout << "*";
                cout << endl;
                cout << "|Do you want to change the ID of book? Enter 1 to change: ";
                cin >> change;
                if (change == 1)
                {
                    cout << "|Enter book ID: ";
                    cin >> q->data.BookID;
                    change = 0;
                }
                cout << "|Do you want to change the title of the book? Enter 1 to change: ";
                cin >> change;
                if (change == 1)
                {
                    cout << "|Enter book title: ";
                    cin >> q->data.bookTitle;
                    change = 0;
                }
                cout << "|Do you want to change the price of book? Enter 1 to change: ";
                cin >> change;
                if (change == 1)
                {
                    cout << "|Enter book price: ";
                    cin >> q->data.bookPrice;
                    change = 0;
                }
                cout << "|Do you want to change the original price of book? Enter 1 to change: ";
                cin >> change;
                if (change == 1)
                {
                    cout << "|Enter original book price: ";
                    cin >> q->data.originalBookPrice;
                    change = 0;
                }
                cout << "|Do you want to change the total of book? Enter 1 to change: ";
                cin >> change;
                if (change == 1)
                {
                    cout << "|Enter totals book: ";
                    cin >> q->data.totalBooks;
                    change = 0;
                }
                cout << "|Do you want to change the number of books sold? Enter 1 to change: ";
                cin >> change;
                if (change == 1)
                {
                    cout << "|Enter books soul: ";
                    cin >> q->data.booksSold;
                    change = 0;
                }
                q->data.booksRemaining = q->data.totalBooks - q->data.booksSold;
                cout << "|The number of books remaining: " << q->data.booksRemaining << endl;
                for (int j = 0; j < 85; j++)
                    cout << "*";
                cout << endl;
                printItem(i);
                return 1;
            };
            q = q->next;
            i++;
        }
        return 0;
    }
    int changeItem(int &p)
    {
        if (head == NULL)
            return 0;
        while (p <= 0 || p > len)
        {
            cout << "Enter the appropriate location: ";
            cin >> p;
        };
        Node *q = head;
        int i = 1;
        while (i != p)
        {
            q = q->next;
            i++;
        };
        int change;
        printItem(i);
        cout << " << Re-enter book information." << endl;
        for (int j = 0; j < 85; j++)
            cout << "*";
        cout << endl;
        cout << "|Do you want to change the ID of book? Enter 1 to change: ";
        cin >> change;
        if (change == 1)
        {
            cout << "|Enter book ID: ";
            cin >> q->data.BookID;
            change = 0;
        }
        cout << "|Do you want to change the title of the book? Enter 1 to change: ";
        cin >> change;
        if (change == 1)
        {
            cout << "|Enter book title: ";
            cin >> q->data.bookTitle;
            change = 0;
        }
        cout << "|Do you want to change the price of book? Enter 1 to change: ";
        cin >> change;
        if (change == 1)
        {
            cout << "|Enter book price: ";
            cin >> q->data.bookPrice;
            change = 0;
        }
        cout << "|Do you want to change the original price of book? Enter 1 to change: ";
        cin >> change;
        if (change == 1)
        {
            cout << "|Enter original book price: ";
            cin >> q->data.originalBookPrice;
            change = 0;
        }
        cout << "|Do you want to change the total of book? Enter 1 to change: ";
        cin >> change;
        if (change == 1)
        {
            cout << "|Enter total books: ";
            cin >> q->data.totalBooks;
            change = 0;
        }
        cout << "|Do you want to change the number of books sold? Enter 1 to change: ";
        cin >> change;
        if (change == 1)
        {
            cout << "|Enter books soul: ";
            cin >> q->data.booksSold;
            change = 0;
        }
        q->data.booksRemaining = q->data.totalBooks - q->data.booksSold;
        cout << "|The number of books remaining: " << q->data.booksRemaining << endl;
        for (int j = 0; j < 85; j++)
            cout << "*";
        cout << endl;
        printItem(i);
        return 1;
    }

    // Gop hai danh sach
    void addRange()
    {
        string filename;
        cout << " >> Enter the file name you want to merge: ";
        cin >> filename;
        readfile(filename);
    }

    // kiem tra thong tin sach
    void check(Book &s)
    {
        while (s.BookID < 10000000 || s.BookID > 99999999 || searchItem(s.BookID) == 1)
        {
            cout << " << Book ID must be 8 digits (10000000 -999999999) without repeating !!!\
                \n >> Enter book ID: ";
            cin >> s.BookID;
        }
        while (s.bookPrice < 1000)
        {
            cout << " << The selling price must be more than 1,000 VND !!!\
                \n >> Enter book price: ";
            cin >> s.bookPrice;
        }
        while (s.originalBookPrice < 1000)
        {
            cout << " << The original price must be more than 1,000 VND !!!\
                \n >> Enter original book price: ";
            cin >> s.originalBookPrice;
        }
        while (s.totalBooks < s.booksSold || s.booksRemaining != s.totalBooks - s.booksSold)
        {
            cout << " << number of books with errors!!!" << endl;
            cout << " >> Enter total books: ";
            cin >> s.totalBooks;
            cout << " >> Enter books sold: ";
            cin >> s.booksSold;
            s.booksRemaining = s.totalBooks - s.booksSold;
            cout << " >> The number of books remaining: " << s.booksRemaining << endl;
        }
    }

    // in danh sach
    void printList()
    {
        Node *n = head;
        int i = 1;
        cout << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << "\n|STT"
             << setw(9) << left << "|ID"
             << setw(21) << left << "|Title"
             << setw(10) << left << "|Price"
             << setw(10) << left << "|ORI Price"
             << setw(10) << left << "|Sold"
             << setw(10) << left << "|Remaining"
             << setw(10) << left << "|Total"
             << "|" << endl;
        while (n != NULL)
        {
            cout << "|" << setw(3) << left << "---"
                 << "|" << setw(8) << left << "--------"
                 << "|" << setw(20) << left << "--------------------"
                 << "|" << setw(9) << left << "---------"
                 << "|" << setw(9) << left << "---------"
                 << "|" << setw(9) << left << "---------"
                 << "|" << setw(9) << left << "---------"
                 << "|" << setw(9) << left << "---------"
                 << "|" << endl;
            cout << "|" << setw(3) << left << i++
                 << "|" << setw(8) << left << n->data.BookID
                 << "|" << setw(20) << left << n->data.bookTitle
                 << "|" << setw(9) << left << n->data.bookPrice
                 << "|" << setw(9) << left << n->data.originalBookPrice
                 << "|" << setw(9) << left << n->data.booksSold
                 << "|" << setw(9) << left << n->data.booksRemaining
                 << "|" << setw(9) << left << n->data.totalBooks
                 << "|" << endl;
            n = n->next;
        }
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
    }
    void printItem(int p)
    {
        Node *n = head;
        int i = 1;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << "\n|STT"
             << setw(9) << left << "|ID"
             << setw(21) << left << "|Title"
             << setw(10) << left << "|Price"
             << setw(10) << left << "|ORI Price"
             << setw(10) << left << "|Sold"
             << setw(10) << left << "|Remaining"
             << setw(10) << left << "|Total"
             << "|" << endl;
        while (i < p)
        {
            n = n->next;
            i++;
        }
        cout << "|" << setw(3) << left << i
             << "|" << setw(8) << left << n->data.BookID
             << "|" << setw(20) << left << n->data.bookTitle
             << "|" << setw(9) << left << n->data.bookPrice
             << "|" << setw(9) << left << n->data.originalBookPrice
             << "|" << setw(9) << left << n->data.booksSold
             << "|" << setw(9) << left << n->data.booksRemaining
             << "|" << setw(9) << left << n->data.totalBooks
             << "|" << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
    }

    // file
    int readfile(string filename)
    {
        string line;
        ifstream file(filename);
        if (!file)
        {
            cout << " << This file does not exist." << endl;
            return 0;
        }
        getline(file, line);
        while (getline(file, line))
        {
            int i = 0;
            Book book;
            string cell[8];
            for (char c : line)
            {
                if (c == ',')
                {
                    ++i;
                }
                else
                {
                    cell[i] += c;
                }
            }
            book.BookID = stoul(cell[1]);
            book.bookTitle = cell[2];
            book.bookPrice = stoul(cell[3]);
            book.originalBookPrice = stoul(cell[4]);
            book.booksSold = stoul(cell[5]);
            book.booksRemaining = stoul(cell[6]);
            book.totalBooks = stoul(cell[7]);
            addLast(book); // Lưu  sach vào DS
        }
        return 1;
    }
    void writefile(string filename)
    {
        Node *n = head;
        int i = 0;
        ofstream file(filename, ios::trunc);
        if (file.is_open())
        {
            file << "STT,ID,Title,Price,ORI Price,Sold,Remaining,Total\n";
            while (n != NULL)
            {
                file << i << ","
                     << n->data.BookID << ","
                     << n->data.bookTitle << ","
                     << n->data.bookPrice << ","
                     << n->data.originalBookPrice << ","
                     << n->data.booksSold << ","
                     << n->data.booksRemaining << ","
                     << n->data.totalBooks << ","
                     << "\n";
                ++i;
                n = n->next;
            }
            file.close();
        }
        else
            cout << "Unable to open file";
    }
    int createfile(string filename)
    {
        ifstream file(filename);
        if (file)
        {
            cout << " << This file already exists." << endl;
            return 0;
        }
        else
        {
            ofstream file(filename, ios::trunc);
        };
        return 1;
    }

    // Nhap n phan tu vao danh sach
    void impItem(Book &s)
    {
        cout << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << "\n|Enter book ID: ";
        cin >> s.BookID;
        cout << "|Enter book title: ";
        cin >> s.bookTitle;
        cout << "|Enter book price: ";
        cin >> s.bookPrice;
        cout << "|Enter original book price: ";
        cin >> s.originalBookPrice;
        cout << "|Enter total books: ";
        cin >> s.totalBooks;
        cout << "|Enter books soul: ";
        cin >> s.booksSold;
        s.booksRemaining = s.totalBooks - s.booksSold;
        cout << "|The number of books remaining: " << s.booksRemaining << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
    }
    void impList(List &l, int n, int m)
    {
        Book s;
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 85; j++)
                cout << "-";
            cout << "\n|Enter book ID: ";
            cin >> s.BookID;
            cout << "|Enter book title: ";
            cin >> s.bookTitle;
            cout << "|Enter book price: ";
            cin >> s.bookPrice;
            cout << "|Enter original book price: ";
            cin >> s.originalBookPrice;
            cout << "|Enter total books: ";
            cin >> s.totalBooks;
            cout << "|Enter books soul: ";
            cin >> s.booksSold;
            s.booksRemaining = s.totalBooks - s.booksSold;
            cout << "|The number of books remaining: " << s.booksRemaining << endl;
            for (int j = 0; j < 85; j++)
                cout << "-";
            cout << endl;
            if (m == 0)
            {
                l.addFirst(s);
            }
            else
            {
                l.addLast(s);
            };
        }
    }
};

// List bán hàng sử dụng cấu trúc array
struct Sell
{
    int day = 0;
    int mon = 0;
    int year = 0;
    unsigned long BillID = 0;
    unsigned long totalBill = 0;
};
struct Sales
{
private:
    Sell data[MAX];
    int len = 0;
    int maxLen = MAX;

public:
    int isEmpty() { return len == 0; }
    int isFull() { return len == maxLen; }
    int getLen() { return len; }
    int getMaxLen() { return maxLen; }

    // them vao vi tri cuoi
    int addlast(Sell s){
        if (isFull())
        {
            cout << " >> FULL list, cannot add! " << endl;
            return 0;
        }
        data[len] = s;
        len++;
        return 1;
    }

    // xoa bo vi tri bt ky
    void removeItem(int &p){
        while (p <= 0 || p > len)
        {
            cout << " >> Enter the appropriate location: ";
            cin >> p;
        };
        for (int i = p - 1; i < len - 1; i++)
        {
            data[i] = data[i + 1];
        }
        len--;
    }

    // in danh sach
    void printList()
    {
        cout << endl;
        for (int j = 0; j < 46; j++)
            cout << "-";
        cout << "\n|STT"
             << setw(6) << left << "|Day"
             << setw(6) << left << "|Month"
             << setw(6) << left << "|Year"
             << setw(13) << left << "|ID"
             << setw(10) << left << "|Total"
             << "|" << endl;
        for (int i = 1; i <= len; i++)
        {
            cout << "|" << setw(3) << left << "---"
                 << "|" << setw(5) << left << "-----"
                 << "|" << setw(5) << left << "-----"
                 << "|" << setw(5) << left << "-----"
                 << "|" << setw(12) << left << "------------"
                 << "|" << setw(9) << left << "---------"
                 << "|" << endl;
            cout << "|" << setw(3) << left << i
                 << "|" << setw(5) << left << data[i].day
                 << "|" << setw(5) << left << data[i].mon
                 << "|" << setw(5) << left << data[i].year
                 << "|" << setw(12) << left << data[i].BillID
                 << "|" << setw(9) << left << data[i].totalBill
                 << "|" << endl;
        }
        for (int j = 0; j < 46; j++)
            cout << "-";
        cout << endl;
    }
    void printItem(int &p)
    {
        while (p <= 0 || p > len)
        {
            cout << " >> Enter the appropriate location: ";
            cin >> p;
        };
        for (int j = 0; j < 46; j++)
            cout << "-";
        cout << "\n|STT"
             << setw(6) << left << "|Day"
             << setw(6) << left << "|Month"
             << setw(6) << left << "|Year"
             << setw(13) << left << "|ID"
             << setw(10) << left << "|Total"
             << "|" << endl;

        cout << "|" << setw(3) << left << p
             << "|" << setw(5) << left << data[p].day
             << "|" << setw(5) << left << data[p].mon
             << "|" << setw(5) << left << data[p].year
             << "|" << setw(12) << left << data[p].BillID
             << "|" << setw(9) << left << data[p].totalBill
             << "|" << endl;
        for (int j = 0; j < 46; j++)
            cout << "-";
        cout << endl;
    }

    // tim kiem
    void binarySearch(unsigned long x)
    {
        int left = 0;
        int right = len;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (data[mid].BillID == x)
                printItem(mid);
            if (data[mid].BillID < x)
                left = mid + 1;

            else
                right = mid - 1;
        }
    }
    void Search(int day, int month, int year)
    {
        int left = 0;
        int right = len;
        for (int i = 1; i <= len; i++)
        {
            if (data[i].year == year || year == NULL)
            {
                if (data[i].mon == month || month == NULL)
                {
                    if (data[i].day == day || day == NULL)
                    {
                        printItem(i);
                    }
                }
            }
        }
    }

    // file
    int readfile(string filename)
    {
        string line;
        ifstream file(filename);
        if (!file)
        {
            cout << " << This file does not exist." << endl;
            return 0;
        }
        getline(file, line);
        while (getline(file, line))
        {
            int i = 0;
            Sell sell;
            string cell[6];
            for (char c : line)
            {
                if (c == ',')
                {
                    ++i;
                }
                else
                {
                    cell[i] += c;
                }
            }
            sell.day = stoi(cell[1]);
            sell.mon = stoi(cell[2]);
            sell.year = stoi(cell[3]);
            sell.BillID = stoul(cell[4]);
            sell.totalBill = stoul(cell[5]);
            addlast(sell); // Lưu  sach vào DS
        }
        return 1;
    }
    int writefile(string filename)
    {
        ofstream file(filename, ios::trunc);
        if (file.is_open())
        {
            file << "STT,Day,Month,Year,ID,Total\n";
            for (int i = 1; i <= len; i++)
            {
                file << i << ","
                     << data[i].day << ","
                     << data[i].mon << ","
                     << data[i].year << ","
                     << data[i].BillID << ","
                     << data[i].totalBill << ","
                     << "\n";
            }
            file.close();
        }
        else
            cout << "Unable to open file";
        return 1;
    }
};

// Tao hoa don su dung cau truc linked List
struct Node1
{
    buyBook data;
    Node1 *next;
};
struct Bill
{
private:
    Node1 *head = NULL;
    string BillID;
    unsigned long totalBill = 0;
    int len = 0;
    int maxLen = MAX;

public:
    void create_id()
    {
        auto now = chrono::system_clock::now();
        time_t time_now = chrono::system_clock::to_time_t(now);

        // Chuyen doi thoi gian sang dinh dang tm
        tm *time_info = localtime(&time_now);

        ostringstream id_stream;
        id_stream << setfill('0') << setw(2) << time_info->tm_hour
                  << setw(2) << time_info->tm_min
                  << setw(2) << time_info->tm_sec
                  << setw(2) << time_info->tm_mday
                  << setw(2) << (time_info->tm_mon + 1)
                  << setw(2) << (time_info->tm_year + 1900) % 100;

        BillID = id_stream.str();
    }
    int isEmpty() { return len == 0; }
    int isFull() { return len == maxLen; }
    int getLen() { return len; }
    int getMaxLen() { return maxLen; }

    // Tra ve phan tu truoc phan tu thu p
    Node1 *getPreItem(int &p)
    {
        if (head == NULL)
            return NULL;
        while (p <= 0 || p > len)
        {
            cout << " >> Enter the appropriate location: ";
            cin >> p;
        };
        if (p == 1)
            return NULL;
        Node1 *q = head;
        for (int i = 2; i < p; i++)
        {
            q = q->next;
        }
        return q;
    }
    // Tra ve phan tu thu p
    Node1 *getItem(int &p)
    {
        if (head == NULL)
            return NULL;
        while (p <= 0 || p > len)
        {
            cout << " >> Enter the appropriate location: ";
            cin >> p;
        };
        Node1 *q = head;
        for (int i = 1; i < p; i++)
        {
            q = q->next;
        }
        return q;
    }

    // them vao vi tri cuoi
    void addLast(buyBook x)
    {
        Node1 *p = new Node1();
        p->data = x;
        p->next = NULL;
        if (head == NULL)
        {
            head = p;
        }
        else
        {
            Node1 *q = head;
            while (q->next != NULL)
                q = q->next;
            q->next = p;
        }
        len++;
    }

    // Xoa vi tri bat ky
    int removeItem(int p, List l)
    {
        Node *s;
        Node1 *Pre_p = getPreItem(p);
        if (Pre_p != NULL)
        {
            Node1 *q;
            q = Pre_p;
            Pre_p = Pre_p->next;
            q->next = Pre_p->next;
        }
        else
        {
            if (head != NULL)
            {
                Pre_p = head;
                head = Pre_p->next;
            }
        };
        l.searchItem(Pre_p->data, s);
        s->data.booksSold = s->data.booksSold - Pre_p->data.quantity;
        s->data.booksRemaining = s->data.booksRemaining + Pre_p->data.quantity;
        totalBill = totalBill - (Pre_p->data.bookPrice * Pre_p->data.quantity);
        delete Pre_p;
        len--;
    }

    // Chinh sua
    void changeItem(int p, List l)
    {
        Node *s;
        Node1 *q = getItem(p);
        l.searchItem(q->data, s);
        s->data.booksSold = s->data.booksSold - q->data.quantity;
        s->data.booksRemaining = s->data.booksRemaining + q->data.quantity;
        totalBill = totalBill - (q->data.bookPrice * q->data.quantity);
        cout << " << You want to change the number of books purchased. ";
        printItem(p);
        do
        {
            cout << " >> Enter Quantity: ";
            cin >> q->data.quantity;
        } while (q->data.quantity > s->data.booksRemaining);
        s->data.booksSold = s->data.booksSold + q->data.quantity;
        s->data.booksRemaining = s->data.booksRemaining - q->data.quantity;
        totalBill = totalBill + (q->data.bookPrice * q->data.quantity);
    }

    // Tao hoa don
    void impBill(List l)
    {
        buyBook sm;
        Node *s;
        int next;
        int i = 1;

        cout << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(47) << right << "BILL" << setw(42);
        do
        {
            cout << "\n| STT: " << i++ << endl;
            do
            {
                cout << "| Enter book ID: ";
                cin >> sm.BookID;
            } while (l.searchItem(sm, s) != 1);
            do
            {
                cout << "| Enter Quantity: ";
                cin >> sm.quantity;
            } while (sm.quantity > s->data.booksRemaining);
            s->data.booksSold = s->data.booksSold + sm.quantity;
            s->data.booksRemaining = s->data.booksRemaining - sm.quantity;
            totalBill = totalBill + (sm.bookPrice * sm.quantity);
            addLast(sm);
            cout << " >> Enter 1 to buy more books: ";
            cin >> next;
        } while (next == 1);
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
    }

    // In va Tinh tong hoa don
    void printList()
    {
        int i = 1;
        Node1 *n = head;
        cout << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
        cout << "|" << setw(43) << right << "BILL" << setw(41) << "|" << endl
             << "|" << setw(41) << right << "BILL ID: " << BillID << setw(31) << "|" << endl
             << "|" << setw(84) << right << "|" << endl
             << "|" << setw(13) << right << "STT"
             << "|" << setw(8) << left << "ID"
             << "|" << setw(20) << left << "Title"
             << "|" << setw(9) << left << "Price"
             << "|" << setw(9) << left << "Quantity"
             << "|" << setw(19) << left << "Total"
             << "|" << endl;
        while (n != NULL)
        {
            cout << "|" << setw(13) << right << i++
                 << "|" << setw(8) << left << n->data.BookID
                 << "|" << setw(20) << left << n->data.bookTitle
                 << "|" << setw(9) << left << n->data.bookPrice
                 << "|" << setw(9) << left << n->data.quantity
                 << "|" << setw(19) << left << n->data.bookPrice * n->data.quantity
                 << "|" << endl;
            n = n->next;
        }
        cout << "|" << setw(84) << right << "|" << endl;
        cout << setw(10) << left << "|"
             << setw(20) << left << "Total bill: "
             << setw(40) << right << totalBill
             << setw(5) << left << " VND"
             << setw(10) << right << "|" << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
    }
    void printItem(int p)
    {
        int i = 1;
        Node1 *n = head;
        cout << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
        cout << "|" << setw(13) << right << "STT"
             << "|" << setw(8) << left << "ID"
             << "|" << setw(20) << left << "Title"
             << "|" << setw(9) << left << "Price"
             << "|" << setw(9) << left << "Quantity"
             << "|" << setw(19) << left << "Total"
             << "|" << endl;

        while (i < p)
        {
            n = n->next;
            i++;
        }
        cout << "|" << setw(13) << right << i
             << "|" << setw(8) << left << n->data.BookID
             << "|" << setw(20) << left << n->data.bookTitle
             << "|" << setw(9) << left << n->data.bookPrice
             << "|" << setw(9) << left << n->data.quantity
             << "|" << setw(19) << left << n->data.bookPrice * n->data.quantity
             << "|" << endl;
        for (int j = 0; j < 85; j++)
            cout << "-";
        cout << endl;
    }

    // Suat hoa don thanh file
    void writefile(List l)
    {
        ofstream file("Bill/" + BillID + ".txt", ios::trunc);
        if (file.is_open())
        {
            int i = 1;
            Node1 *n = head;
            file << endl;
            for (int j = 0; j < 85; j++)
                file << "-";
            file << endl;
            file << "|" << setw(43) << right << "BILL" << setw(41) << "|" << endl
                 << "|" << setw(41) << right << "BILL ID: " << BillID << setw(31) << "|" << endl
                 << "|" << setw(84) << right << "|" << endl
                 << "|" << setw(13) << right << "STT"
                 << "|" << setw(8) << left << "ID"
                 << "|" << setw(20) << left << "Title"
                 << "|" << setw(9) << left << "Price"
                 << "|" << setw(9) << left << "ORI Price"
                 << "|" << setw(19) << left << "Quantity"
                 << "|" << endl;
            while (n != NULL)
            {
                file << "|" << setw(13) << right << i++
                     << "|" << setw(8) << left << n->data.BookID
                     << "|" << setw(20) << left << n->data.bookTitle
                     << "|" << setw(9) << left << n->data.bookPrice
                     << "|" << setw(9) << left << n->data.quantity
                     << "|" << setw(19) << left << n->data.bookPrice * n->data.quantity
                     << "|" << endl;
                n = n->next;
            }
            file << "|" << setw(84) << right << "|" << endl;
            file << setw(10) << left << "|"
                 << setw(20) << left << "Total bill: "
                 << setw(40) << right << totalBill
                 << setw(5) << left << " VND"
                 << setw(10) << right << "|" << endl;
            for (int j = 0; j < 85; j++)
                file << "-";
            file << endl;
            file.close();
            cout << " << File.txt created successfully." << endl;
            l.writefile("khosach.csv");
        }
        else
        {
            cout << " << Can't create file.txt." << endl;
        }
    }
};

int menu_List2(List DS, string filename)
{
    system("cls");
    int mode;
    int n;
    Book s;
    while (1)
    {
        cout << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(45) << right << "GROUP 5" << setw(39) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Vo Phuong Thao - 20119029" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Xuan Hai       - 20119221" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Anh Hao        - 20119222" << setw(26) << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(42) << right << "MENU" << setw(42)
             << "|" << setw(85) << left << "\n| 1. Add n books to the list."
             << "|" << setw(85) << left << "\n| 2. Add a book at position p."
             << "|" << setw(85) << left << "\n| 3. Add a book at the beginning of the list."
             << "|" << setw(85) << left << "\n| 4. Add a book at the end of the list."
             << "|" << setw(85) << left << "\n| 5. Remove a book at position p."
             << "|" << setw(85) << left << "\n| 6. Remove a book at the beginning of the list."
             << "|" << setw(85) << left << "\n| 7. Remove a book at the end of the list."
             << "|" << setw(85) << left << "\n| 8. Change book information by ID."
             << "|" << setw(85) << left << "\n| 9. Change book information by position."
             << "|" << setw(85) << left << "\n| 10. Search the list by name."
             << "|" << setw(85) << left << "\n| 11. Search the list by ID."
             << "|" << setw(85) << left << "\n| 12. Search the list by position."
             << "|" << setw(85) << left << "\n| 13. Print the list."
             << "|" << setw(85) << left << "\n| 14. Merge two lists into one."
             << "|" << setw(85) << left << "\n| 15. Sort the list."
             << "|" << setw(85) << left << "\n| 0. Exit."
             << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << "\n >> Select: ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            cout << " >> Add n books to the list. n = ";
            cin >> n;
            DS.impList(DS, n, 1);
            break;
        case 2:
            cout << " >> Add a book at position p. p = ";
            cin >> n;
            DS.impItem(s);
            DS.addItem(DS.getItem(n), s);
            break;
        case 3:
            cout << " >> Add a book at the beginning of the list: " << endl;
            DS.impList(DS, 1, 0);
            break;
        case 4:
            cout << " >> Add a book at the end of the list: " << endl;
            DS.impList(DS, 1, 1);
            break;
        case 5:
            cout << " >> Remove a book at position p. p = ";
            cin >> n;
            DS.removeItem(DS.getItem(n));
            break;
        case 6:
            cout << " >> Remove a book at the beginning of the list: " << endl;
            DS.removeFirst();
            break;
        case 7:
            cout << " >> Remove a book at the end of the list: " << endl;
            DS.removeLast();
            break;
        case 8:
            cout << " >> Change book information by ID: ";
            cin >> s.BookID;
            DS.changeItem(s.BookID);
            break;
        case 9:
            cout << " >> Change book information by position: ";
            cin >> n;
            DS.changeItem(n);
            break;
        case 10:
            cout << " >> Search the list by name: ";
            cin >> s.bookTitle;
            DS.searchItem(s.bookTitle);
            break;
        case 11:
            cout << " >> Search the list by ID: ";
            cin >> s.BookID;
            DS.searchItem(s.BookID);
            break;
        case 12:
            cout << " >> Search the list by position. p = ";
            cin >> n;
            DS.searchItem(DS.getItem(n)->data.bookTitle);
            break;
        case 13:
            cout << " >> Print the list: " << endl;
            DS.printList();
            break;
        case 14:
            cout << " >> Erge two lists into one: " << endl;
            DS.addRange();
            break;
        case 15:
            cout << " >> Sort the list: " << endl;
            DS.sortList();
            break;
        case 0:
            DS.writefile(filename);
            return 1;
        default:
            cout << " >> RETYPE!!!" << endl;
            break;
        }
    }
    return 0;
}

int menu_list1()
{
    string filename;
    int mode;
    while (1)
    {
        List DS;
        system("cls");
        cout << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(45) << right << "GROUP 5" << setw(39) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Vo Phuong Thao - 20119029" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Xuan Hai       - 20119221" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Anh Hao        - 20119222" << setw(26) << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(42) << right << "MENU" << setw(42)
             << "|" << setw(85) << left << "\n| 1. Read file.csv: list."
             << "|" << setw(85) << left << "\n| 2. Create file.csv: new list."
             << "|" << setw(85) << left << "\n| 0. Exit."
             << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << "\n >> Select: ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            cout << " >> Enter the name file.csv to open: ";
            cin >> filename;
            if (DS.readfile(filename + ".csv"))
                menu_List2(DS, filename + ".csv");
            break;
        case 2:
            cout << " >> Enter the name file.csv to create a new list: ";
            cin >> filename;
            if (DS.createfile(filename + ".csv"))
                menu_List2(DS, filename + ".csv");
            break;
        case 0:
            return 1;
        default:
            cout << " >> RETYPE!!!";
            break;
        }
    }
    return 0;
}

int menu_bill()
{
    system("cls");
    int mode;
    int n;
    List DS;
    Bill HD;
    HD.create_id();
    DS.readfile("khosach.csv");
    while (1)
    {
        cout << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(45) << right << "GROUP 5" << setw(39) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Vo Phuong Thao - 20119029" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Xuan Hai       - 20119221" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Anh Hao        - 20119222" << setw(26) << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(43) << right << "MENU" << setw(41)
             << "|" << setw(85) << left << "\n| 1. Add n books to the bill."
             << "|" << setw(85) << left << "\n| 2. Remove a book at position p."
             << "|" << setw(85) << left << "\n| 3. Change book information by position."
             << "|" << setw(85) << left << "\n| 4. Print the bill."
             << "|" << setw(85) << left << "\n| 5. Export invoice file."
             << "|" << setw(85) << left << "\n| 0. Exit."
             << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << "\n >> Select: ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            cout << " >> Add n books to the bill. " << endl;
            HD.impBill(DS);
            break;
        case 2:
            cout << " >> Remove a book at position p. p = ";
            cin >> n;
            HD.removeItem(n, DS);
            break;
        case 3:
            cout << " >> Change book information by position p. p = ";
            cin >> n;
            HD.changeItem(n, DS);
            break;
        case 4:
            cout << " >> Print the bill." << endl;
            HD.printList();
            break;
        case 5:
            cout << " >> Export invoice file." << endl;
            HD.writefile(DS);
            break;
        case 0:
            return 1;
        default:
            cout << " >> RETYPE!!!";
            break;
        }
    }
    return 0;
}

int menu_Sales()
{
}

int main()
{
    int mode;
    while (1)
    {
        system("cls");
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(45) << right << "GROUP 5" << setw(39) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Vo Phuong Thao - 20119029" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Xuan Hai       - 20119221" << setw(26) << "|" << endl
             << "|" << setw(58) << right << "Nguyen Anh Hao        - 20119222" << setw(26) << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << endl;
        cout << "|" << setw(52) << right << "BOOK STRORE MANAGER" << setw(32)
             << "|" << setw(85) << left << "\n|1. List book."
             << "|" << setw(85) << left << "\n|2. Create bill."
             << "|" << setw(85) << left << "\n|3. Sales list."
             << "|" << setw(85) << left << "\n|0. Exit."
             << "|" << endl;
        for (int i = 0; i < 85; i++)
            cout << "*";
        cout << "\n >> Select: ";
        cin >> mode;
        switch (mode)
        {
        case 1:
            menu_list1();
            break;
        case 2:
            menu_bill();
            break;
        case 3:
            menu_Sales();
            break;
        case 0:
            return 1;
        default:
            cout << " >> RETYPE!!!";
            break;
        }
    };
    return 0;
}
