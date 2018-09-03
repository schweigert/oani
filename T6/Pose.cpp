#include "Pose.h"

/**
\brief Construtor padrao para a classe Pose
*/
Pose::Pose()
{}
/**
\brief Construtor clonagem padrao para a classe Pose
\param oClone objeto a ser clonado
*/
Pose::Pose( const Pose& oClone )
{
	this->listOfPoseAttribs = oClone.listOfPoseAttribs;
	this->dMomentInTime     = oClone.dMomentInTime;
}
/**
\brief Construtor clonagem para ponteiros da classe Pose
\param ptrClone ponteiro para um objeto a ser clonado
*/
Pose::Pose( Pose* ptrClone )
{
	this->listOfPoseAttribs = ptrClone->listOfPoseAttribs;
	this->dMomentInTime     = ptrClone->dMomentInTime;
}
/**
  \brief Define o momento quando esta pose deve ocorrer no tempo durante a animacao
  \param dMomentInTime momento no tempo (em milisegundos) quando a pose deve ocorrer
*/
void Pose::setTime( double dMomentInTime )
{
	this->dMomentInTime = dMomentInTime;
}
/**
  \brief Adiciona mais um atributo animavel a pose a ser animada
  \param ptrPoseAttr ponteiro para o novo atributo animavel a ser adicionado a pose
*/
void Pose::addPoseAttribute( PoseAttribute* ptrPoseAttr )
{
	this->listOfPoseAttribs.push_back( ptrPoseAttr );
}
/**
  \brief Modifica o valor de um certo atributo animavel da pose
  \param ptrPoseAttr ponteiro para o atributo animavel a ser modificado na pose
  \param uiIndex posicao do atributo na pose
  \return flag que indica sucesso na operacao
*/
bool Pose::setPoseAttribute( PoseAttribute* ptrPoseAttr, unsigned int uiIndex )
{
	if( uiIndex < this->listOfPoseAttribs.size() )
	{
		this->listOfPoseAttribs[ uiIndex ] = ptrPoseAttr;
		return true;
	}
	return false;
}
/**
  \brief Retorna um atributo animavel especifico pertencente a pose com base em sua posicao na lista
  \param uiIndex posicao do atributo na pose
  \return ponteiro ao atributo animavel em questao ou nulo se indice invalido
*/
PoseAttribute* Pose::getPoseAttribute( unsigned int uiIndex )
{
	if( uiIndex < this->listOfPoseAttribs.size() )
		return this->listOfPoseAttribs[ uiIndex ];

	return NULL;
}
/**
  \brief Retorna um atributo animavel especifico pertencente a pose com base em seu nome
  \param strName nome do atributo procurado
  \return atributo animavel em questao ou nulo se indice invalido
*/
PoseAttribute* Pose::getPoseAttribute( string strName )
{
	for( vector<PoseAttribute*>::iterator poseAttr = this->listOfPoseAttribs.begin();
		poseAttr != this->listOfPoseAttribs.end(); poseAttr++ )
	{
		if( (* poseAttr )->getLabel() == strName )
		{
			return (* poseAttr );
		}
	}

	return NULL;
}
/**
   \brief Verifica se o pose vector contem um atributo interpolavel com um dado nome
   \param strAttrName nome do atributo interpolavel a ser verificado
   \return flag que indica a existencia ou nao do dado atributo
*/
bool Pose::hasPoseAttributeName( string strAttrName )
{
	for( vector<PoseAttribute*>::iterator poseAttr = this->listOfPoseAttribs.begin();
		poseAttr != this->listOfPoseAttribs.end(); poseAttr++ )
	{
		if( (* poseAttr )->getLabel() == strAttrName )
		{
			return true;
		}
	}
	return false;
}
