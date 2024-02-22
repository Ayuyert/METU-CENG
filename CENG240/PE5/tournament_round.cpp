#include "tournament_round.h"

// TournamentRound functions goes here

TournamentRound::TournamentRound() { }
TournamentRound::TournamentRound(std::list<MusicBand*>_bands) { }
TournamentRound::TournamentRound(std::vector<MusicBand*>_bands) { }

std::size_t TournamentRound::size() { return -1; }
    
//TournamentRound::TournamentRound(TournamentRound& other) { }
//TournamentRound::TournamentRound(TournamentRound&& other) { }
TournamentRound& TournamentRound::operator=(TournamentRound&& other) { return *this; }
TournamentRound& TournamentRound::get_next_round() { return *this; }

std::ostream& operator<< (std::ostream &os, TournamentRound &other) { return os; }
