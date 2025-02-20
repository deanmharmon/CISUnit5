// CISUnit5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Dean Mason
//2/20/2025
//Program Description: To allow customers to make a purchase, utilizing discounts and additional fees, giving bill at the end
//Description update: Utilizes functions to allow a menu so that users can run the options as many times as they want


#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

//Declaring constants that will be used throughout the program
const double BRONZE = 100.00;
const double SILVER = 200.00;
const double POUND_RATE = 2.65;
const double MILE_RATE = 0.45;
const double WW_WEIGHT = 16;
const double AP_WEIGHT = 16;
const double BW_WEIGHT = 16;
const double OZ_PER_LB = 16;
const double buckwheatPrice = 5.0;
const double wholeWheatPrice = 6.5;
const double allPurposePrice = 3.5;
const double TAX_RATE = 0.075;
const double CASH_DISCOUNT = 0.1;
const double FINANCE_FEE = 0.15;
const int REWARD_CHOICE = 1;
const int ORDER_CHOICE = 2;
const int BILL_CHOICE = 3;
const int EXIT = 4;
const double STOCK_HIGH = 400.0;


bool validate(double purchase = 0.0, double stock = STOCK_HIGH)
{
    if (purchase < 0)
    {
        cout << "You did not enter a positive value, please retry\n";
        return false;
    }
    if (purchase > stock)
    {
        cout << "You attempted to order more than allowed, please retry\n";
        return false;
    }
    else return true;
}

string rewardRank(double previousSpent) 
{
    string currentStatus; 
    double upgradePrice; 
    string nextTier; 
    

    if (previousSpent > 0.0 && previousSpent <= BRONZE)
    {
        currentStatus = "Bronze";
        upgradePrice = BRONZE - previousSpent; 
        nextTier = "Silver";
        cout << "You are a " << currentStatus << " rewards member\n";
        return currentStatus;
    }
    else if (previousSpent > BRONZE && previousSpent < SILVER)  
    {
        currentStatus = "Silver";
        upgradePrice = SILVER - previousSpent; 
        nextTier = "Gold";
        cout << "You are a " << currentStatus << " rewards member\n";
        return currentStatus;
    }
    else if (previousSpent >= SILVER) 
    {
        currentStatus = "Gold";
        upgradePrice = 0;
        cout << "You are a " << currentStatus << " rewards member\n";
        return currentStatus;
    }
    else
    {
        cout << "Unfortunately you did not enter a valid number. Please run the command again and enter a valid number!" << endl;
        return currentStatus;
    }
}

int newOrder(string type, int stock_type)
{
    // we use type to make this reusable, as well as stock_type to run in the validation function
    int purchase;
    cout << "\nHow many pounds of " << type << " would you like ? ";
    cin >> purchase;
    if (validate(purchase, stock_type)) {
        return purchase;
    }
    else
    {
        return 0;
    }

}

//we take all of these as arguments to be able to work with anything given by running previous program aspects
double billEnd(int buckwheatPurchase, int wholeWheatPurchase, int allPurposePurchase, double previousSpent, string Name, string currentStatus)
{
    //vars must be declaed here to do math
    double discount;
    double distCost;
    double poundCost;
    double totalWeight;
    double deliveryTotal;
    double totalBW;
    double totalWW;
    double totalAP;
    double totalBillPre;
    double taxCash;
    double cashBill;
    double finalCash;
    double avgCashPPI;
    double avgCreditPPI;
    double newTotal;
    double taxCredit;
    double creditBill;
    double finalCredit;
    double finance;
    double onlineOrderTot;
    int method;
    int totalItem;
    int financeCharge = 1;
    string Address; 
    double mileage; 
   
    if (currentStatus == "Gold")
    {
        financeCharge = 0;
    }

    cout << "\n\n\nHow would you like to place your order? ";
    cout << "\nEnter 1 for cash \nEnter 2 for Card \nEnter 3 for Web Order ";
    cin >> method; 

    //math math
    totalItem = buckwheatPurchase + allPurposePurchase + wholeWheatPurchase;
    totalBW = buckwheatPrice * buckwheatPurchase;
    totalWW = wholeWheatPrice * wholeWheatPurchase;
    totalAP = allPurposePrice * allPurposePurchase;
    totalBillPre = totalBW + totalWW + totalAP;

    if (validate(method))
    {

        switch (method) {
        case 1:
            //math for cash
            discount = (totalBillPre * CASH_DISCOUNT);
            cashBill = totalBillPre - discount;
            taxCash = cashBill * TAX_RATE;
            finalCash = taxCash + cashBill;
            avgCashPPI = finalCash / totalItem;
            newTotal = previousSpent + finalCash;

            cout << "-------------CASH BILL---------------\n";
            cout << setw(35) << left << "Total Price Before Discount: $" << setw(13) << right << fixed << setprecision(2) << totalBillPre << endl;
            cout << setw(35) << left << "Tax Amount: $" << setw(13) << right << fixed << setprecision(2) << taxCash << endl;
            cout << setw(35) << left << "Discount Amount: $" << setw(13) << right << fixed << setprecision(2) << discount << endl;
            cout << setw(35) << left << "Subtotal: $" << setw(13) << right << fixed << setprecision(2) << finalCash << endl;
            cout << setw(35) << left << "Average cost per item: $" << setw(13) << right << fixed << setprecision(2) << avgCashPPI << endl;
            cout << setw(35) << left << "New total amount spent: " << setw(13) << right << fixed << setprecision(2) << newTotal << endl;
            return newTotal;
            break;

        case 2:
            //math, the financeCharge being 1 unless the if statement for gold allows the clunky version of this to work. I put too much time in to make it better this version.
            finance = (totalBillPre * FINANCE_FEE) * financeCharge;
            creditBill = totalBillPre + finance;
            taxCredit = creditBill * TAX_RATE;
            finalCredit = taxCredit + creditBill;
            avgCreditPPI = finalCredit / totalItem;
            newTotal = previousSpent + finalCredit;

            cout << "\n\n\n-------------CREDIT BILL -----------------\n";
            cout << setw(35) << left << "Subtotal: $" << setw(13) << right << fixed << setprecision(2) << totalBillPre << endl;
            cout << setw(35) << left << "Tax Amount: $" << setw(13) << right << fixed << setprecision(2) << taxCredit << endl;
            cout << setw(35) << left << "Finance Charge Amount: $" << setw(13) << right << fixed << setprecision(2) << finance << endl;
            cout << setw(35) << left << "Subtotal with tax & finance fee: $" << setw(13) << right << fixed << setprecision(2) << finalCredit << endl;
            cout << setw(35) << left << "Average price per item: $" << setw(13) << right << fixed << setprecision(2) << avgCreditPPI << endl;
            cout << setw(35) << left << "New total amount spent: " << setw(13) << right << fixed << setprecision(2) << newTotal << endl;
            return newTotal; 
            break;


        case 3:
            cout << "\nEnter an address for your order please: ";
            cin.ignore();
            getline(cin, Address);
            cout << "\nEnter the distance (in miles) from the store: ";
            cin >> mileage;

            //math
            finance = (totalBillPre * FINANCE_FEE) * financeCharge;
            creditBill = totalBillPre + finance;
            taxCredit = creditBill * TAX_RATE;
            finalCredit = taxCredit + creditBill;
            avgCreditPPI = finalCredit / totalItem;

            //boring
            totalWeight = (buckwheatPurchase * (BW_WEIGHT / OZ_PER_LB)) + (allPurposePurchase * (AP_WEIGHT / OZ_PER_LB)) + (wholeWheatPurchase * (WW_WEIGHT / OZ_PER_LB));
            distCost = MILE_RATE * mileage;
            poundCost = totalWeight * POUND_RATE;
            deliveryTotal = distCost + poundCost;
            onlineOrderTot = deliveryTotal + finalCredit;
            newTotal = onlineOrderTot + previousSpent;

            cout << "\n\n\n-------------CREDIT BILL -----------------\n";
            cout << setw(35) << left << "Subtotal: $" << setw(13) << right << fixed << setprecision(2) << totalBillPre << endl;
            cout << setw(35) << left << "Tax Amount: $" << setw(13) << right << fixed << setprecision(2) << taxCredit << endl;
            cout << setw(35) << left << "Finance Charge Amount: $" << setw(13) << right << fixed << setprecision(2) << finance << endl;
            cout << setw(35) << left << "Subtotal with tax & finance fee: $" << setw(13) << right << fixed << setprecision(2) << finalCredit << endl;
            cout << setw(35) << left << "Average price per item: $" << setw(13) << right << fixed << setprecision(2) << avgCreditPPI << endl;


            //i did not include the ounces section because flour is typically not sold by the ounce, but the math above works it would be very simple to add if the product were changed
            cout << "\n\n-------------SHIPPING REPORT-----------------\n";
            cout << "Customer Name: " << Name << endl;
            cout << "Shipping to: " << Address << endl;
            cout << setw(35) << left << "\n\nDistance Cost: " << setw(15) << right << fixed << setprecision(2) << distCost << endl;
            cout << setw(35) << left << "Pound Cost: " << setw(13) << right << fixed << setprecision(2) << poundCost << endl;
            cout << setw(35) << left << "Total Shipping cost: " << setw(13) << right << fixed << setprecision(2) << deliveryTotal << endl;
            cout << endl;
            cout << setw(35) << left << "ONLINE ORDER TOTAL: " << setw(13) << right << fixed << setprecision(2) << onlineOrderTot << endl;
            cout << setw(35) << left << "New total amount spent: " << setw(13) << right << fixed << setprecision(2) << newTotal << endl;
            return newTotal;
            break;


        default:
            cout << "You have not entered an appropriate selection, please try again!";
            return 0;
        }

        
    }
    else
    {
        cout << "You entered an invalid selection, please try again\n";
    }
}

int main()
{
    //declaring vars
    //must be initialized to 0 to work without user input
    //must be set to zero at initialization so that if they do not input a previous amount, it will still work
    double previousSpent = 0;
    int buckwheatPurchase = 0;
    int wholeWheatPurchase = 0;
    int allPurposePurchase = 0;
    double newRank;
    int bwStock = 174;
    int wwStock = 200;
    int apStock = 354;
    string Name;
    string currentStatus; 
    bool loop = true; 
    int selection; 
    string rewardStatus;  
    string bw = "Buckwheat";
    string ap = "All Purpose";
    string ww = "Whole Wheat";

    //Giving info for pricing to customers

    cout << "Good afternoon and welcome to Insane Grains!\nJust a heads up, all of my bags are 1lb and I'm not splitting them open!\n";
    cout << "For sale today we have:\n";
    cout << bwStock << " pounds of Buckwheat at $" << buckwheatPrice << " each.\n";
    cout << wwStock << " pounds of Whole wheat at $" << wholeWheatPrice << " each.\n"; 
    cout << apStock << " pound of All-Purpose at $" << allPurposePrice << " each.\n";

    //getting the order in, telling reward status
    cout << "\nPlease enter the name for your order please: ";
    getline(cin, Name);

    //main menu loop
    while (loop)
    {
        cout << "Enter 1 to determine your reward rank\n";
        cout << "Enter 2 to purchase our products\n";
        cout << "Enter 3 to display your bill and reward level\nExit\n";
        cin >> selection; 
        
        switch (selection)
        {
        case REWARD_CHOICE:
            //gets the previous spent, validates, and then runs the rewardRank function if it validates
            cout << "\nHow much have you spent at Insane Grains?: $";
            cin >> previousSpent;
            if (validate(previousSpent))
            {
                rewardStatus = rewardRank(previousSpent);
            }
            else
            {
                break;
            }
            break;
        case ORDER_CHOICE:
            //runs each individually to make for less code in the function
            //each will be verified individually
            buckwheatPurchase = newOrder(bw, bwStock);
            wholeWheatPurchase = newOrder(ww, wwStock);
            allPurposePurchase = newOrder(ap, apStock);

            break;
        case BILL_CHOICE:
            newRank = billEnd(buckwheatPurchase, wholeWheatPurchase, allPurposePurchase, previousSpent, Name, rewardStatus);
            rewardRank(newRank);
            //this updates previousSpent afte running
            previousSpent = newRank;
            break;
            //since they will type a string to exit, any non int 1-3 will give this result
        default:
            loop = false;
            break;
        }
        
    }
    return 0;
}