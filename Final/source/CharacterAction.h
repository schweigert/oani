#ifndef _CHARACTER_ACTION_H_
#define _CHARACTER_ACTION_H_

#include "Keyframing.h"
#include <string>
#include <vector>
using namespace std;

/**
  \class CharacterAction
  \brief A animacao de uma acao de um personagem articulado e dada pela combinacao de objetos Keyframing para cada junta da hierarquia do modelo.<br>
  \sa Character()
*/
class CharacterAction
{
public:
	enum JointType
	{
		TORSO = 0,  ///< torax do personagem
		HEAD,       ///< pescoco e cabeca
		ARM_LEFT,   ///< braco esquerdo
		ARM_RIGHT,  ///< braco direito
		HAND_LEFT,  ///< mao esquerda
		HAND_RIGHT, ///< mao direita
		LEG_LEFT,   ///< perna esquerda
		LEG_RIGHT,  ///< perna direita
		FOOT_LEFT,  ///< pe esquerdo
		FOOT_RIGHT  ///< pe direito
	};

private:
	string              strActionName;      ///< nome da acao
	vector<Keyframing*> listOfJointActions; ///< conjunto de animacao de cada articulacao de um personagem que define uma acao

public:
	CharacterAction();
	CharacterAction( const CharacterAction& );
	CharacterAction( CharacterAction* );
	~CharacterAction();
	/**
	  \brief Retorna o nome da acao deste objeto
	  \return nome da acao corrente
	*/
	inline string getActionName() { return this->strActionName; }
	void setActionName( string );

	void setAction( Keyframing*, CharacterAction::JointType );
	Keyframing* getAction( CharacterAction::JointType );
	/**
	  \brief Retorna a quantidade de articulacoes associada a este modelo articulado
	  \return tamanho do esqueleto (numero de articulacoes) do modelo corrente
	*/
	inline unsigned int getNumberOfJoints() { return this->listOfJointActions.size(); }
};

#endif
