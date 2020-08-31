/*
Rutik Pol
0120180213
*/

//Unification Algorithm, works flawlessly for simple queries

#include<iostream>
#include<string>
#include<stack>

using namespace std;
string substitutions = "";

class expr
{
public:
    string name;
    stack<expr> args;

    void express (string tree)
    {
        cout << "Defining " << tree << endl;

        cout << "Expression name : ";
        cin >> this->name;

        cout << "Nested expressions? : ";
        int arg_count;
        cin >> arg_count;

        for(int i=0; i<arg_count; i++)
        {
            string pseudo_name = tree + name + "_" + char(i + 48) + " >";

            expr temp;
            temp.express(pseudo_name);

            args.push(temp);
        }
    }
};

string appearance(expr e, string rets = "")
{
    rets += e.name;
    if(!e.args.empty())
    {
        rets += "[ ";
        while(!e.args.empty())
        {
            rets += appearance(e.args.top());
            e.args.pop();

            if(!e.args.empty()) rets += ", ";
        }
        rets += " ]";
    }

    return rets;
}

string unify(expr lhs, expr rhs)
{
    if(lhs.args.size() == 0 || rhs.args.size() == 0)
    {
        if(lhs.name == rhs.name)
        {
            return "NIL";
        }
     
        else if(isupper(lhs.name[0]))
        {

            if(appearance(rhs).find(lhs.name) != std::string::npos)
            {
                cout << endl << appearance(rhs) << endl << lhs.name << endl;
                return "FAILURE Ψ1 occurs in Ψ2";
            }
            else
            {
                string rets = "{" + appearance(lhs) + "/" + appearance(rhs) + "}";
                return rets;
            }
        }
        else if(isupper(rhs.name[0]))
        {

            if(appearance(lhs).find(rhs.name) != std::string::npos)
            {
                cout << endl << appearance(lhs) << endl << rhs.name << endl;
                cout << appearance(lhs).find(rhs.name) << endl;
                return "FAILURE Ψ2 occurs in Ψ1";
            }
            else
            {
                string rets = "{" + appearance(rhs) + "/" + appearance(lhs) + "}";
                return rets;
            }
        }
        else
        {
            cout << lhs.name << "|" << rhs.name << endl;
            return "FAILURE all constants";
        }
    }

    if(lhs.name != rhs.name)
        return "FAILURE different predicates";

    if(lhs.args.size() != rhs.args.size())
        return "FAILURE argument count mismatch";

    while(!lhs.args.empty())
    {

        string S = unify(lhs.args.top(), rhs.args.top());

        lhs.args.pop();
        rhs.args.pop();

        if(S.find("FAILURE") != std::string::npos)
        {
       
            cout << S << endl;
            return S;
        }
    
        if(S != "NIL")
        {

            {
                substitutions = substitutions + S + "\n";
            }
        }
    }
 
    return substitutions;
}

int main()
{
   cout << "Please enter the number of predicates : ";
   int predicate_count;
   cin >> predicate_count;

   expr predicates[predicate_count];

    cout << endl;
    for(int i=0; i<predicate_count; i++)
    {
        cout << "\nEnter your predicate " << i << " :-\n";

        string pseudo_name = "";
        pseudo_name = pseudo_name + char(i+48) + "_";

        predicates[i].express(pseudo_name);
    }
    cout << endl << endl;

    cout << "Predicates you've entered are :-\n";
    for(int i=0; i<predicate_count; i++)
    {
        cout << i << " " << appearance(predicates[i]) << endl;
    }
    cout << endl << endl;

    for(int i=0; i<predicate_count; i++)
    {
        for(int j=0; j<predicate_count; j++)
        {
            if(i==j) continue;

            cout << "....\nUnifying";
            cout << "\n> " << appearance(predicates[i]);
            cout << "\n> " << appearance(predicates[j]);
            cout << endl;

            substitutions = "";
            cout << unify(predicates[i], predicates[j]);
            cout << "....\n\n";
        }
    }
}
