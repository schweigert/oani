#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "PivotedBRep.h"
#include "CharacterAction.h"
#include <string>
#include <vector>
using namespace std;

/**
  \class Character
  \brief Classe do tipo personagem articulado composto de sub-partes. A cada personagem esta associado uma lista de acoes (animacoes pre-definidas)
  \sa CharacterAction()
*/
class Character: public PivotedBRep
{
private:
	unsigned int uiPolyCount; ///< numero de poligonos deste personagem
	vector<CharacterAction*> Repertoire;  ///< lista que contem todas as possiveis animacoes para este personagem
	CharacterAction* ptrCurrentAction; ///< armazena o ponteiro para a animacao sendo executada (deve ser uma das acoes na lista Repertoire)

	void walk();

public:
	Character();
	Character( const Character& );
	Character( Character* );
	~Character();

	void OnLoad( string );

	void addAction( CharacterAction* );
	CharacterAction* getAction( unsigned int );
	CharacterAction* getAction( string );
	void setAction( string );
	/**
	  \brief Retorna a quantidade de acoes associada a este personagem
	  \return o tamanho da lista Repertoire
	*/
	inline unsigned int getNumberOfActions() { return this->Repertoire.size(); }
	/**
	  \brief Retorna a acao sendo atualmente executada para este personagem
	  \return ponteiro para a acao corrente sendo executada
	*/
	inline CharacterAction* whichActionIsPlaying() { return this->ptrCurrentAction; }

	virtual void OnLoop( double );
	/**
	  \brief Retorna o numero de poligonos associado a este personagem
	  \return quantidade de poligonos do personagem
	*/
	inline unsigned int getPolyCount() { return this->uiPolyCount; }
};

#endif
