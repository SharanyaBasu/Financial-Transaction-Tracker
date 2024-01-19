#include <cassert>
#include <iomanip>
#include <iostream>
#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////


// Constructor
Transaction::Transaction( std::string ticker_symbol, unsigned int day_date, unsigned int
month_date, unsigned year_date, bool buy_sell_trans, unsigned int number_shares,
double trans_amount)
{
    symbol=ticker_symbol;
    day=day_date;
    month=month_date;
    year=year_date;
    
    if (buy_sell_trans==true)
        trans_type="Buy";
    else
        trans_type="Sell";
    shares=number_shares;
    amount=trans_amount;
    
    acb=0;
    acb_per_share=0;
    share_balance=0;
    cgl=0;
    p_next=nullptr;
    trans_id= assigned_trans_id;
    ++assigned_trans_id;
    
};

// Destructor
Transaction::~Transaction()
{
    
}

// Overloaded < operator.
bool Transaction::operator<( Transaction const &other )
{
    if (year<other.year)
        return true;
    else if (year>other.year)
        return false;
    else if (month<other.month)
        return true;
    else if (month>other.month)
        return false;
    else if(day<other.day)
        return true;
    else if (day>other.day)
        return false;
    else if (trans_id<other.trans_id)
        return true;
    else
        return false;
        
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////


// Constructor
History::History()
{
    p_head=nullptr;
}

// Destructor
History::~History()
{
    Transaction *item=p_head;
    Transaction *temp;
    if (p_head!=nullptr)
    {
        while (item !=nullptr)
        {
            temp=item ->get_next();
            delete item;
            item = temp;
        }
    }
    p_head=nullptr;
}


// insert(...): Insert transaction into linked list.
void History::insert(Transaction *p_new_trans)
{
    Transaction *item=p_head;
    
    if (p_head==nullptr)
        p_head=p_new_trans;
    else
    {
        while (item ->get_next()!=nullptr)
        {
            item=item->get_next();
        }
        item ->set_next(p_new_trans);
    }
}

// read_history(...): Read the transaction history from file.
void History::read_history()
{
    ece150::open_file();
    
    while (ece150::next_trans_entry()==true)
    {
        Transaction *p_new_trans = new Transaction(ece150::get_trans_symbol(), ece150::get_trans_day(), ece150::get_trans_month(), ece150::get_trans_year(), ece150::get_trans_type(), ece150::get_trans_shares(), ece150::get_trans_amount());
       
        insert(p_new_trans);
    }
    
    ece150::close_file();
}


// print() Print the transaction history.
void History::print()
{
    std::cout<<"========== BEGIN TRANSACTION HISTORY ============"<<std::endl;
    Transaction *item=p_head;
    while (item !=nullptr)
    {
        item -> print();
        item = item ->get_next();
    }
    std::cout<<"========== END TRANSACTION HISTORY ============"<<std::endl;
}


// sort_by_date(): Sort the linked list by trade date.

void History::sort_by_date()
{
    Transaction *sorted = nullptr;

    while (p_head != nullptr)
    {
        Transaction *largest = p_head;
        Transaction *search = p_head;
        Transaction *prev = nullptr;

        while (search->get_next() != nullptr)
        {
            if (*largest < *search->get_next())
            {
                prev = search;
                largest = search->get_next();
            }
            search = search->get_next();
        }

        if (prev != nullptr)
        {
            prev->set_next(largest->get_next());
        }
        else
        {
            p_head = largest->get_next();
        }

        largest->set_next(sorted);
        sorted = largest;
    }

    p_head = sorted;
    sorted = nullptr;
}


// update_acb_cgl(): Updates the ACB and CGL values.
void History::update_acb_cgl()
{
    Transaction *currentTrans = p_head;

    double total_acb = 0.0;
    double total_share = 0.0;
    double acb_per_share = 0.0;

    while (currentTrans != nullptr)
    {
        if (currentTrans->get_trans_type() == true)
        {
            // acb for Buy:
            total_acb += currentTrans->get_amount();
            currentTrans->set_acb(total_acb);

            // Share balance for Buy:
            total_share += currentTrans->get_shares();
            currentTrans->set_share_balance(total_share);

            // acb per share for Buy:
            acb_per_share = total_acb / total_share;
            currentTrans->set_acb_per_share(acb_per_share);
        }
        else
        {
            // acb per share for Sell:
            currentTrans->set_acb_per_share(acb_per_share);

            // acb for Sell:
            double sell_acb = currentTrans->get_shares() * acb_per_share;
            total_acb -= sell_acb;
            currentTrans->set_acb(total_acb);

            // Share balance for Sell:
            total_share -= currentTrans->get_shares();
            currentTrans->set_share_balance(total_share);

            // cgl for Sell:
            currentTrans->set_cgl(currentTrans->get_amount() - sell_acb);
        }
        currentTrans = currentTrans->get_next();
    }
    
    currentTrans=nullptr;
}

// compute_cgl(): )Compute the ACB, and CGL.
double History::compute_cgl(unsigned int year)
{
    Transaction *currentTrans=p_head;
    double total=0.0;
    while(currentTrans!=nullptr)
    {
        if(currentTrans->get_year()==year)
        {
            if (currentTrans->get_trans_type()==false)
            {
                double cgl = currentTrans->get_amount()-currentTrans->get_shares()*currentTrans->get_acb_per_share();
                total=total+cgl;
            }
        }
        currentTrans=currentTrans->get_next();
    }
    return total;
}

// GIVEN
// get_p_head(): Full access to the linked list.
Transaction *History::get_p_head() { return p_head; }
