CARDHEADERS = Card.hpp Item.hpp Follower.hpp Holding.hpp Personality.hpp 

OBJS = main.o BattlePhase.o Card.o EconomyPhase.o EquipPhase.o FinalPhase.o Follower.o Gameboard.o  Holding.o Item.o Personality.o Player.o Province.o StartingPhase.o TypeConverter.o DeckBuilder.o

PROGRAM = L5Rexe

CFLAGS = -std=c++11 

main.o: main.cpp Gameboard.hpp
	g++ $(CFLAGS) -c main.cpp

Card.o: Card.cpp Card.hpp 
	g++ $(CFLAGS) -c Card.cpp

Item.o: Item.cpp Item.hpp Card.hpp
	g++ $(CFLAGS) -c Item.cpp

Follower.o: Follower.cpp Follower.hpp Card.hpp
	g++ $(CFLAGS) -c Follower.cpp

Holding.o: Holding.cpp Holding.hpp Card.hpp
	g++ $(CFLAGS) -c Holding.cpp

Personality.o: Personality.cpp $(CARDHEADERS)
	g++ $(CFLAGS) -c Personality.cpp

Province.o: Province.cpp Province.hpp Card.hpp
	g++ $(CFLAGS) -c Province.cpp

DeckBuilder.o: DeckBuilder.cpp DeckBuilder.hpp $(CARDHAEADERS)
	g++ $(CFLAGS) -c DeckBuilder.cpp

TypeConverter.o: TypeConverter.cpp TypeConverter.hpp $(CARDHAEADERS) 
	g++ $(CFLAGS) -c TypeConverter.cpp

Player.o: Player.cpp Player.hpp $(CARDHAEADERS) DeckBuilder.hpp
	g++ $(CFLAGS) -c Player.cpp

Deckbuilder.o: Deckbuilder.cpp Deckbuilder.hpp $(CARDHEADERS)
	g++ $(CFLAGS) -c Deckbuilder.o

StartingPhase.o: StartingPhase.cpp Player.hpp $(CARDHEADERS) Province.hpp
	g++ $(CFLAGS) -c StartingPhase.cpp

EquipPhase.o: EquipPhase.cpp TypeConverter.hpp Gameboard.hpp Player.hpp $(CARDHAEADERS)
	g++ $(CFLAGS) -c EquipPhase.cpp

BattlePhase.o: BattlePhase.cpp $(CARDHEADERS) Gameboard.hpp Player.hpp 
	g++ $(CFLAGS) -c BattlePhase.cpp

EconomyPhase.o: EconomyPhase.cpp Gameboard.hpp Player.hpp $(CARDHAEADERS)
	g++ $(CFLAGS) -c EconomyPhase.cpp

FinalPhase.o: FinalPhase.cpp Gameboard.hpp Player.hpp $(CARDHEADERS)
	g++ $(CFLAGS) -c FinalPhase.cpp

$(PROGRAM): clean $(OBJS)
	g++ $(CFLAGS) $(OBJS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS)

run: $(PROGRAM)
	./$(PROGRAM)
