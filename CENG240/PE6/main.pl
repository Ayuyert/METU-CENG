:- module(main, [is_vote_wasted/2, is_candidate_elected/2, candidate_count_from_city/3, all_parties/1, all_candidates_from_party/2, all_elected_from_party/2, election_rate/2, council_percentage/2, alternative_debate_setups/2]).
:- [kb].

is_vote_wasted(City, Politicalparty) :-
    candidate(_, Politicalparty, City, _),
    \+ elected(City, Politicalparty, _).

is_candidate_elected(Name, Politicalparty) :-
    candidate(Name, Politicalparty, City, Sira),
    elected(City, Politicalparty, ElectedCount),
    Sira =< ElectedCount.

candidate_count_from_city([], _, 0).

candidate_count_from_city([X|Xs],City , Count) :-
    \+(candidate(X,_,City,_)),
    candidate_count_from_city(Xs, City, Countb),
    Count is Countb.


candidate_count_from_city( [X|Xs] , City , Count ) :-
    candidate(X,_,City,_),
    candidate_count_from_city(Xs, City, Countb),
    Count is Countb + 1.
    


all_parties(Parties) :-
  findall(PoliticalParty, party(PoliticalParty, _), Parties).


all_candidates_from_party(Politicalparty, Candidates) :-
  findall(Candidatename, candidate(Candidatename, Politicalparty, _, _), Candidates).

all_elected_from_party(Politicalparty, List) :-
   findall(Candidatename,is_candidate_elected(Candidatename,Politicalparty), List).

election_rate(PoliticalParty, Percentage) :-
  all_elected_from_party(PoliticalParty, SecilenAday),
  all_candidates_from_party(PoliticalParty, Adaylar),
  length(SecilenAday, Secilensayi),
  length(Adaylar, Adaysayi),
  Percentage is (Secilensayi / Adaysayi).
  
  
council_percentage(PoliticalParty, Percentage) :-
  to_elect(Toplam),
  all_elected_from_party(PoliticalParty, Secilenler),
  length(Secilenler, Secilentoplam),
  Percentage is (Secilentoplam / Toplam).



