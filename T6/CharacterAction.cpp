#include "CharacterAction.h"

/**
  \brief Construtor padrao para a classe CharacterAction
  Cria uma animacao sem movimento para um personagem articulado com articulacoes padrao
*/
CharacterAction::CharacterAction()
{
	for( unsigned int uiJoint = CharacterAction::TORSO; uiJoint <= CharacterAction::FOOT_RIGHT; uiJoint++ )
		this->listOfJointActions.push_back( new Keyframing() );
}
/**
  \brief Construtor clonagem para objetos da classe CharacterAction
  \param oClone objeto da classe a ser clonado
*/
CharacterAction::CharacterAction( const CharacterAction& oClone )
{
	for( unsigned int uiJoint = CharacterAction::TORSO; uiJoint <= CharacterAction::FOOT_RIGHT; uiJoint++ )
		this->listOfJointActions[ uiJoint ] = new Keyframing( oClone.listOfJointActions[ uiJoint ] );
	//this->listOfJointActions = oClone.listOfJointActions;
	this->strActionName = oClone.strActionName;
}
/**
  \brief Construtor clonagem para ponteiros a objetos da classe CharacterAction
  \param ptrClone ponteiro para o objeto da classe a ser clonado
*/
CharacterAction::CharacterAction( CharacterAction* ptrClone )
{
	for( unsigned int uiJoint = CharacterAction::TORSO; uiJoint <= CharacterAction::FOOT_RIGHT; uiJoint++ )
		this->listOfJointActions[ uiJoint ] = new Keyframing( ptrClone->listOfJointActions[ uiJoint ] );
	//this->listOfJointActions = ptrClone->listOfJointActions;
	this->strActionName = ptrClone->strActionName;
}
/**
   \brief Destrutor para objetos da classe CharacterAction
*/
CharacterAction::~CharacterAction()
{
	for( unsigned int uiJoint = CharacterAction::TORSO; uiJoint != CharacterAction::FOOT_RIGHT; uiJoint++ )
		delete this->listOfJointActions[ uiJoint ];
}
/**
  \brief Define o nome do objeto acao
  \param strActionName nome da acao corrente
*/
void CharacterAction::setActionName( string strActionName )
{
	this->strActionName = strActionName;
}
/**
  \brief Define o objeto Keyframing associado com uma das articulacoes do personagem animado
  \param ptrKeyframing ponteiro para o objeto animador (Keyframing) a ser associado
  \param joint articulacao respectiva a ser modificada
*/
void CharacterAction::setAction( Keyframing* ptrKeyframing, CharacterAction::JointType joint )
{
	if( ptrKeyframing ) // previne a adi�ao de objetos nulos
		this->listOfJointActions[ joint ] = ptrKeyframing;
}
/**
  \brief Retorna o objeto animador associado a uma articulacao especifica
  \param joint articulacao para a qual deve ser retornado o objeto animador associado
  \return ponteiro ao objeto animador (Keyframing) associado
*/
Keyframing* CharacterAction::getAction( CharacterAction::JointType joint )
{
	return this->listOfJointActions[ joint ];
}
