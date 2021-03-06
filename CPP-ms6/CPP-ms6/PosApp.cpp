#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "NonPerishable.h"
#include "Perishable.h"
#include "PosApp.h"


using namespace std;

namespace ict {
	PosApp::PosApp(const char* filename, const char* billfname) {
		strcpy(m_filename, filename);
		strcpy(m_billfname, billfname);
		m_noOfItems = 0;
		loadRecs();
	}
	int PosApp::menu() {
		int select;
		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add Perishable item" << endl;
		cout << "3- Add Non-Perishable item" << endl;
		cout << "4- Update item quantity" << endl;
		cout << "5- Show Item" << endl;
		cout << "6- POS" << endl;
        cout << "7- Sort" <<endl;
		cout << "0- exit program" << endl;
		cout << "> " ;
		cin >> select;
		if (cin.fail() || select < 0 || select > 7) {
			cin.clear();
			cin.ignore();
			select = -1;
		}
		return select;
	}
	void PosApp::deallocateItems() {
		int j;
		for (j = 0; j < m_noOfItems; j++) {
		     // delete m_items[j];
			m_items[j] = nullptr;
		}
		m_noOfItems = 0;
	}
	void PosApp::loadRecs() {
		Item* item;
		deallocateItems();
		int j = 0;

		fstream dataFile;
		dataFile.open(m_filename, ios::in);
        
		if (dataFile.fail()) {
            dataFile.clear();
			dataFile.close();
			dataFile.open(m_filename, ios::out);
			dataFile.close();
		}
		else {
           

			char idChar;
			while (dataFile.get(idChar)) {
				if (idChar == 'N') {
					item = new NonPerishable();
					item->load(dataFile);
					m_items[j] = item;
					j++;
				}
				else if (idChar == 'P') {
					item = new Perishable();
					item->load(dataFile);
					m_items[j] = item;
					j++;
				}
			}
			m_noOfItems = j;
           

			dataFile.close();
		}

	}
	void PosApp::saveRecs() {
		fstream dataFile;
		int qty = 0;
		int j = 0;

		dataFile.open(m_filename, ios::out);
		for (j = 0; j < m_noOfItems; j++) {
			qty = m_items[j]->quantity();
			if (qty > 0)
				m_items[j]->save(dataFile);
		}
		dataFile.clear();
		dataFile.close();
		loadRecs();
	}
	int PosApp::searchItems(const char* sku)const {
		int i = 0;
		int foundIndex = -1;
		for (i = 0; i < m_noOfItems; i++) {
			if (!(strcmp(m_items[i]->sku(), sku))) {
				foundIndex = i;
				i = m_noOfItems;
			}
		}

		return foundIndex;
	}
	void PosApp::updateQty() {
		char sku[50];
		int foundIndex;
		int origQty;
		int newQty;
		int updatedQty;
		cout << "Please enter the SKU: ";
		cin >> sku;
		foundIndex = searchItems(sku);
		if (foundIndex == -1) {
			cout << "Not found!" << endl;

		}
		else {
			m_items[foundIndex]->write(cout, false);
			cout << endl;
			cout << "Please enter the number of purchased items: ";
			cin >> newQty;
			origQty = m_items[foundIndex]->quantity();
			updatedQty = newQty + origQty;
			m_items[foundIndex]->quantity(updatedQty);
			saveRecs();
			cout << "Updated!" << endl;
			cout << endl;
		}
	}
	void PosApp::addItem(bool isPerishable) {
		fstream dataFile;
		Item* item;

		dataFile.open(m_filename, ios::out | ios::app);
		if (dataFile.fail()) {
			dataFile.open(m_filename, ios::out);
		}
		if (isPerishable)
			item = new Perishable();
		else
			item = new NonPerishable();

		item->read(cin);
		if (cin.fail()) {
			item->write(cout, false);
			cin.clear();
			cout << endl;
		}
		else {
			m_items[m_noOfItems] = item;
			m_items[m_noOfItems]->save(dataFile);
			m_noOfItems++;
			cout << "Item added." << endl;
			cout << endl;
		}


	}
	void PosApp::listItems()const {
		double totalCost = 0;
		int i = 0;
        
		if (m_noOfItems == 0) {
			cout << "No item!" << endl;
			cout << endl;
		}
		else if (m_noOfItems > 0) {

			cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
			cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
			for (i = 0; i < m_noOfItems; i++) {
				cout << setw(4) << setfill(' ') << i + 1 << " | ";
				m_items[i]->write(cout, true);
				cout << endl;
				totalCost = totalCost + m_items[i]->cost() * m_items[i]->quantity();

			}

			cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
			cout << setw(48) << setfill(' ') << "Total Asset: $  |" << setw(14) << setfill(' ') << totalCost << '|' << endl;
			cout << "-----------------------------------------------^--------------^" << endl;
			cout << endl;


		}
	}
	void PosApp::truncateBillFile() {
		fstream dataFile;
		dataFile.open(m_billfname, ios::out | ios::trunc);
		dataFile.close();
	}

	void PosApp::showBill() {
		fstream dataFile;
		Item* item;
		double totalCost = 0;
		char idChar;
		time_t currentTime;
		struct tm * timeinfo;
		char buff[80];

		time(&currentTime);
		timeinfo = localtime(&currentTime);

		strftime(buff, sizeof(buff), "%d/%m/%Y, %I:%M", timeinfo);

		string currentDT(buff);

		dataFile.open(m_billfname, ios::in);

		cout << "v--------------------------------------------------------v" << endl;
		cout << "|"<<currentDT<<"                                       |" << endl;
		cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
		cout << "|--------|--------------------|-------|---|----|---------|" << endl;
		while (dataFile.get(idChar)) {


			if (idChar == 'P') {
				item = new Perishable();
				item->load(dataFile);
				cout << "| ";
				item->write(cout, true);
				totalCost = totalCost + item->cost();
				cout << endl;
			}

			else if (idChar == 'N') {
				item = new NonPerishable();
				item->load(dataFile);
				cout << "| ";
				item->write(cout, true);
				totalCost = totalCost + item->cost();
				cout << endl;
			}

		/*
		item->load(dataFile);
		cout << "| ";
		item->write(cout, true);
		totalCost = totalCost + item->cost();
		cout << endl;*/

		}

		cout << "^--------^--------------------^-------^---^----^---------^" << endl;
		cout << "|" << setw(42) << setfill(' ') << "Total: $  |" << setw(14) << setfill(' ') << totalCost << '|' << endl;
		cout << "^-----------------------------------------^--------------^" << endl << endl;
		dataFile.close();
		truncateBillFile();
	}
	void PosApp::addToBill(Item& I) {

		fstream dataFile;
		int qty = I.quantity();

		dataFile.open(m_billfname, ios::out | ios::app);
		if (dataFile.fail()) {
			dataFile.open(m_billfname, ios::out);
		}

		I.quantity(1);
		I.save(dataFile);

		I.quantity(qty - 1);
		saveRecs();

	}

	void PosApp::POS() {
		char skuTemp[50];
		int indexFound;
		int flag = 0;
		fstream dataFile;
		dataFile.open(m_billfname, ios::out | ios::app);
		if (dataFile.fail()) {
			dataFile.open(m_billfname, ios::out);
		}

		while (flag != 1) {
			cout << "Sku: ";
			//cin >> skuTemp;

			cin.getline(skuTemp, 50);

			if (strlen(skuTemp) == 0) {
				showBill();
			     //   cout << "enter here";
				flag = 1;
			}
			else {
				indexFound = searchItems(skuTemp);
				if (indexFound >= 0) {
					cout << "v------------------->" << endl;
					cout << "| " << m_items[indexFound]->name() << endl;
					cout << "^------------------->" << endl;
					addToBill(*m_items[indexFound]);

				}
				else if (indexFound == -1) {
					cout << "Not found!" << endl;

				}
			}
		}

	}
    int PosApp::sortMenu() {
        int select;
        cout << "Sort on:" << endl;
        cout << "1- Sku" << endl;
        cout << "2- Item Name" << endl;
        cout << "3- Price" << endl;
        cout << "4- Quantity" << endl;
        cout << "0- exit Sort" << endl;
        cout << "> " ;
        cin >> select;
        if (cin.fail() || select < 0 || select > 4) {
            cin.clear();
            cin.ignore();
            select = -1;
        }
        return select;
    }
    void PosApp::Sort(){
        int select = 0;
        
        while((select = sortMenu()) != 0){
            switch (select) {
                case 1:
                    sortSku();
                    break;
                case 2:
                    sortName();
                    break;
                case 3:
                    sortPrice();
                    break;
                case 4:
                    sortQty();
                    break;
                default:
                    cout<<endl;
                    cout << "===Invalid Selection, try again===" << endl<<endl;
                    break;
            }
        }
        cout<< "Aborted!"<<endl<<endl;
    }
    int asc(){
        char ans;
        int res = -1;
       
        while(res == -1){
            cout<<endl;
            cout<<"Ascending? (y/n) ";
            cin>>ans;
            if (ans == 'y' || ans == 'n') {
                if(ans == 'y')
                   res = 1;
                else
                    res = 0;
            }
            else {
                cout << "Invalid Entry, (y)es or (n)o"<<endl;
                res = -1;
            }
        }
        return res;
    }
    void PosApp::sortSku(){
        int ans, c, d;
        ans = asc();
        if(ans == 1){
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    const char* first =m_items[d]->sku();
                    const char* second = m_items[d+1]->sku();
                    if(strcmp(first ,second)>0){
                        swap(m_items[d],m_items[d+1]);
                    }
                }
            }
        }else{
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    const char* first =m_items[d]->sku();
                    const char* second = m_items[d+1]->sku();
                    if(strcmp(first ,second) < 0){
                        swap(m_items[d],m_items[d+1]);
                    }
                }
            }
        }
        cout<<endl;
        listItems();
    }
    void PosApp::sortName(){
        int ans, c, d;
        ans = asc();
        if(ans == 1){
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    const char* first =m_items[d]->name();
                    const char* second = m_items[d+1]->name();
                    if(strcmp(first ,second)>0){
                        swap(m_items[d],m_items[d+1]);
                    }
                }
            }
        }else{
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    const char* first =m_items[d]->name();
                    const char* second = m_items[d+1]->name();
                    if(strcmp(first ,second) < 0){
                       swap(m_items[d],m_items[d+1]);
                    }
                }
            }
        }
        cout<<endl;
        listItems();
    }
    void swap(Item* left, Item* right){
        Item* temp;
        temp = left;
        left = right;
        right = temp;

    }
    void PosApp::sortPrice(){ //does not work with swap()
        int ans, c, d;
        ans = asc();
        if(ans == 1){
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    double first = m_items[d]->price();
                    double second = m_items[d+1]->price();
                    if(first > second){
                        Item* temp;
                        temp = m_items[d];
                        m_items[d] = m_items[d+1];
                        m_items[d+1] = temp;
                    }
                }
            }
        }else{
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    double first = m_items[d]->price();
                    double second = m_items[d+1]->price();
                    if(first < second){
                        Item* temp;
                        temp = m_items[d];
                        m_items[d] = m_items[d+1];
                        m_items[d+1] = temp;
                    }
                }
            }
        }
        cout<<endl;
        listItems();
    }
    void PosApp::sortQty(){ //does not work with swap()
        int ans, c, d;
        ans = asc();
        if(ans == 1){
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    int first = m_items[d]->quantity();
                    int second = m_items[d+1]->quantity();
                    if(first > second){
                        Item* temp;
                        temp = m_items[d];
                        m_items[d] = m_items[d+1];
                        m_items[d+1] = temp;
                    }
                }
            }
        }else{
            for(c = 0; c < (m_noOfItems -1); c++){
                for (d = 0; d <  m_noOfItems-c-1; d++){
                    int first = m_items[d]->quantity();
                    int second = m_items[d+1]->quantity();
                    if(first < second){
                        Item* temp;
                        temp = m_items[d];
                        m_items[d] = m_items[d+1];
                        m_items[d+1] = temp;
                    }
                }
            }
        }
        cout<<endl;
        listItems();
    }


	void PosApp::run() {
		char skuTemp[50];
		int indexFound;
		int select;

		while ((select = menu()) != 0) {
			switch (select) {
			case 1:
				cout << endl;
				listItems();
				break;
			case 2:
				cout << endl;
				addItem(true);
				break;
			case 3:
				cout << endl;
				addItem(false);
				break;
			case 4:
				cout << endl;
				updateQty();
				break;
			case 5:
				cout << endl;
				cout << "Please enter the SKU: ";
				cin >> skuTemp;
				indexFound = searchItems(skuTemp);
				if (indexFound > 0) {
					cout << "v-----------------------------------v" << endl;
					m_items[indexFound]->write(cout, false);
					cout << "^-----------------------------------^" << endl;
					cout << endl;
				}
				else if (indexFound == -1) {
					cout << "Not found!" << endl;
				}
				break;
			case 6:
				cout << endl;
				cin.ignore();
				POS();
				break;
            case 7:
                cout<<endl;
                Sort();
                break;
            default:
				cout << "===Invalid Selection, try again===" << endl;
				cout << endl;
			}
		}
		if (select == 0) {
            cout<<endl;
			cout << "Goodbye!" << endl;
		}

	}


}

#include "PosApp.h"
