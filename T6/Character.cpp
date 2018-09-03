#include "Character.h"
#include "PivotedBRep.h"
#include "BRep.h"
/**
  \brief Construtor padrao para a classe Character
  Cria um personagem articulado vazio (sem articulacoes)
*/
Character::Character(): PivotedBRep()
{}
/**
  \brief Construtor clonagem para objetos da classe Character
  \param oClone objeto da classe Character a ser clonado
*/
Character::Character( const Character& oClone ): PivotedBRep( oClone )
{
	for( unsigned int uiAction = 0; uiAction < (( Character )oClone ).getNumberOfActions(); uiAction++ )
		this->addAction( new CharacterAction( (( Character )oClone ).getAction( uiAction ) ) );
}
/**
  \brief Construtor clonagem para ponteiros a objetos da classe Character
  \param ptrClone ponteiro para o objeto da classe Character a ser clonado
*/
Character::Character( Character* ptrClone ): PivotedBRep( ptrClone )
{
	for( unsigned int uiAction = 0; uiAction < ptrClone->getNumberOfActions(); uiAction++ )
		this->addAction( new CharacterAction( ptrClone->getAction( uiAction ) ) );
}
/**
  \brief Destrutor para a classe Character
*/
Character::~Character()
{
	for( vector<CharacterAction*>::iterator ptrAction = this->Repertoire.begin(); ptrAction != this->Repertoire.end(); ptrAction++ )
		delete (* ptrAction );
	this->ptrCurrentAction = NULL;
}
/**
  \brief Adiciona uma nova acao ao repertorio do personagem
  \param ptrAction ponteiro para a nova acao a ser adicionada
*/
void Character::addAction( CharacterAction* ptrAction )
{
	if( ptrAction ) // previne a insercao de ponteiros nulos
		this->Repertoire.push_back( ptrAction );
}
/**
  \brief Retorna uma acao do repertorio do personagem com base em sua posicao na lista
  \param uiIndex posicao da acao na lista repertorio
  \return ponteiro para a dada acao ou nulo caso indice invalido
*/
CharacterAction* Character::getAction( unsigned int uiIndex )
{
	if( uiIndex < this->getNumberOfActions() )
		return this->Repertoire[ uiIndex ];
	return NULL;
}
/**
  \brief Retorna uma acao do repertorio do personagem com base em seu nome
  \param strActionLabel rotulo do nome do acao desejada
  \return ponteiro para a dada acao ou nulo caso indice invalido
*/
CharacterAction* Character::getAction( string strActionLabel )
{
	for( vector<CharacterAction*>::iterator ptrAction = this->Repertoire.begin(); ptrAction != this->Repertoire.end(); ptrAction++ )
		if( (* ptrAction )->getActionName() == strActionLabel )
			return (* ptrAction );
	return NULL;
}
/**
  \brief Atualiza o nome da acao sendo executada
  \param strActionName nome da acao a ser executada
*/
void Character::setAction( string strActionName )
{
	for( vector<CharacterAction*>::iterator ptrAction = this->Repertoire.begin(); ptrAction != this->Repertoire.end(); ptrAction++ )
		if( (* ptrAction )->getActionName() == strActionName )
		{
			this->ptrCurrentAction = (* ptrAction );

			// atualiza os objetos Keyframing para cada articula�ao do personagem
			this->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::TORSO ) );

			this->getChild( 0 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::HEAD ) );

			this->getChild( 0 )->getChild( 1 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::ARM_LEFT ) );
			this->getChild( 0 )->getChild( 1 )->getChild( 0 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::HAND_LEFT ) );

			this->getChild( 0 )->getChild( 2 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::ARM_RIGHT ) );
			this->getChild( 0 )->getChild( 2 )->getChild( 0 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::HAND_RIGHT ) );

			this->getChild( 0 )->getChild( 3 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::LEG_RIGHT ) );
			this->getChild( 0 )->getChild( 3 )->getChild( 0 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::FOOT_RIGHT ) );

			this->getChild( 0 )->getChild( 4 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::LEG_LEFT ) );
			this->getChild( 0 )->getChild( 4 )->getChild( 0 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::FOOT_LEFT ) );
		}
}
/**
  \brief Atualiza os parametros do personagem. Deve ser usado para determinar as animacoes do personagem a cada novo frame da animacao
  \param uiDeltaTime tempo transcorrido desde a ultima chamada de atualizacao
*/
void Character::OnLoop( double dDeltaTime )
{
	// atualiza os objetos Keyframing para cada articula�ao do personagem
	/*this->getChild( 0 )->getKeyframing()->OnLoop( uiDeltaTime );
	this->getChild( 0 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::HEAD ) );
	this->getChild( 0 )->getChild( 1 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::ARM_LEFT ) );
	this->getChild( 0 )->getChild( 1 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::HAND_LEFT ) );
	this->getChild( 0 )->getChild( 2 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::ARM_RIGHT ) );
	this->getChild( 0 )->getChild( 2 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::HAND_RIGHT ) );
	this->getChild( 0 )->getChild( 3 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::LEG_RIGHT ) );
	this->getChild( 0 )->getChild( 3 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::FOOT_RIGHT ) );
	this->getChild( 0 )->getChild( 4 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::LEG_LEFT ) );
	this->getChild( 0 )->getChild( 4 )->getChild( 0 )->setKeyframing( this->ptrCurrentAction->getAction( CharacterAction::FOOT_LEFT ) );*/

	PivotedBRep::OnLoop( dDeltaTime );
}
/**
  \brief Carrega o modelo BRep referente a cada parte do corpo do personagem e monta a estrutura hierarquica do mesmo
*/
void Character::OnLoad( string strPath )
{
	this->uiPolyCount = 0;

	PivotedBRep::OnLoad( strPath + "Boneco-Body.obj" ); // raiz do modelo articulado
	this->uiPolyCount += (( BRep* )this->getChild( 0 ) )->getPolyCount();

	// montando a parte superior do corpo

	PivotedBRep * ptrHeadPivot = new PivotedBRep();
	ptrHeadPivot->OnLoad( strPath + "Boneco-Head.obj" );
	ptrHeadPivot->setTranslate( Vector3( 0.0f, 2.0f, 0.0f ) );
	this->getChild( 0 )->attach( ptrHeadPivot ); // prende a cabeca ao torso
	this->uiPolyCount += (( BRep* )ptrHeadPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrLeftArmPivot = new PivotedBRep();
	ptrLeftArmPivot->OnLoad( strPath + "Boneco-Arm-L.obj" );
	ptrLeftArmPivot->setTranslate( Vector3( 0.7f, 1.8f, 0.0f ) );
	this->getChild( 0 )->attach( ptrLeftArmPivot ); // prende o bra�o esquerdo ao torso
	this->uiPolyCount += (( BRep* )ptrLeftArmPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrLeftHandPivot = new PivotedBRep();
	ptrLeftHandPivot->OnLoad( strPath + "Boneco-Hand-L.obj" );
	ptrLeftHandPivot->setTranslate( Vector3( 1.45f, 0.0f, 0.0f ) );
	ptrLeftArmPivot->getChild( 0 )->attach( ptrLeftHandPivot ); // prende a mao esquerda ao bra�o esquerdo
	this->uiPolyCount += (( BRep* )ptrLeftHandPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrRightArmPivot = new PivotedBRep();
	ptrRightArmPivot->OnLoad( strPath + "Boneco-Arm-R.obj" );
	ptrRightArmPivot->setTranslate( Vector3( -0.7f, 1.8f, 0.0f ) );
	this->getChild( 0 )->attach( ptrRightArmPivot ); // prende o bra�o direito ao torso
	this->uiPolyCount += (( BRep* )ptrRightArmPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrRightHandPivot = new PivotedBRep();
	ptrRightHandPivot->OnLoad( strPath + "Boneco-Hand-R.obj" );
	ptrRightHandPivot->setTranslate( Vector3( -1.45f, 0.0f, 0.0f ) );
	ptrRightArmPivot->getChild( 0 )->attach( ptrRightHandPivot ); // prende a mao direita ao bra�o direito
	this->uiPolyCount += (( BRep* )ptrRightHandPivot->getChild( 0 ) )->getPolyCount();

	// montando a parte inferior do corpo

	PivotedBRep * ptrRightLegPivot = new PivotedBRep();
	ptrRightLegPivot->OnLoad( strPath + "Boneco-Leg.obj" );
	ptrRightLegPivot->setTranslate( Vector3( -0.25f, 0.0f, 0.0f ) );
	this->getChild( 0 )->attach( ptrRightLegPivot ); // prende a perna direita ao torso
	this->uiPolyCount += (( BRep* )ptrRightLegPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrRightFootPivot = new PivotedBRep();
	ptrRightFootPivot->OnLoad( strPath + "Boneco-Foot.obj" );
	ptrRightFootPivot->setTranslate( Vector3( 0.0f, -1.7f, 0.0f ) );
	ptrRightLegPivot->getChild( 0 )->attach( ptrRightFootPivot ); // prende o pe direito a perna direita
	this->uiPolyCount += (( BRep* )ptrRightFootPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrLeftLegPivot = new PivotedBRep();
	ptrLeftLegPivot->OnLoad( strPath + "Boneco-Leg.obj" );
	ptrLeftLegPivot->setTranslate( Vector3( 0.25f, 0.0f, 0.0f ) );
	this->getChild( 0 )->attach( ptrLeftLegPivot ); // prende a perna esquerda ao torso
	this->uiPolyCount += (( BRep* )ptrLeftLegPivot->getChild( 0 ) )->getPolyCount();

	PivotedBRep * ptrLeftFootPivot = new PivotedBRep();
	ptrLeftFootPivot->OnLoad( strPath + "Boneco-Foot.obj" );
	ptrLeftFootPivot->setTranslate( Vector3( 0.0f, -1.7f, 0.0f ) );
	ptrLeftLegPivot->getChild( 0 )->attach( ptrLeftFootPivot ); // prende o pe esquerdo a perna esquerda
	this->uiPolyCount += (( BRep* )ptrLeftFootPivot->getChild( 0 ) )->getPolyCount();
}
