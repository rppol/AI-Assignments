assignDur(DS, 234, 345).
assignDur(ML, 345, 456).
assignDur(DL, 245, 375).
assignDur(WT, 564, 896).
assignDur(DEM, 654, 100).

workQuestion(DS, 25).
workQuestion(ML, 22).
workQuestion(DL, 35).
workQuestion(WT, 17).
workQuestion(DEM, 33).

number(DS, 2).
number(ML, 3).
number(DL, 4).
number(WT, 5).
number(DEM, 6).


/*Greater than and Equal to operations!*/
task(X, Y) :- assignDur(X, A, B),
    Y>=A,
    Y=<B.
/*OUTPUT :
?- task(X, 1350).
X = ML ;
X = DL ;
false.
*/


/*Using division and subtraction operator*/
workRate(X, Y):- assignDur(X, A, B), workQuestion(X, C),
    Y is C/(B-A).
/* OUTPUT :
?- workRate(DS, Y).
Y = 0.18018018018018017.
*/


/*Using multiplication operator*/
totalTime(X, Y):- assignDur(X, A, B), number(X, C),
    Y is C*(B-A).
/* OUTPUT :
?- totalTime(DS, Y).
Y = 222.
*/

/*Using multiplication operator*/
addWorkandNumber(X, Y):- workQuestion(X, C), number(X, D),
    Y is C+D.
/* OUTPUT :
?- addWorkandNumber(DS, Y).
Y = 22.
*/

/*Using loop*/
/* sum of integers from 1 to N inclusive */
sumto(1, 1).
sumto(N, M) :- N>1, N1 is N-1, sumto(N1, M1), M is M1+N.
/*
?- sumto(10,N).
N = 55 .
*/
