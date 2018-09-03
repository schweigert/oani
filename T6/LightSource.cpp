#include "LightSource.h"
#include "VectorAttribute.h"
#include "FloatAttribute.h"

/**
  \brief Construtor padrao para a classe LightSource
  Cria um objeto fonte de luz padrao = luz pontual na cor branca
  \param uiIndex indice da fonte de luz a ser criada (valores validos 0-7)
  \param lightType tipo da fonte de luz sendo criada
*/
LightSource::LightSource( unsigned int uiIndex, LightSource::LightSourceType lightType ) : ColoredEntity()
{
	this->Type                  = lightType;
	this->bActive               = true;
	this->vAmbientColor         = ( (Vector3) Vector3::WHITE ) * 0.2f; // tom de cinza 20%
	this->vSpecularColor        = Vector3::WHITE;
	this->vDirection            = ( (Vector3)Vector3::UNIT_Y ) * -1.0f; // vertical para baixo
	this->fExponent             = 0.0f;
	this->fCuttOff              = 30.0f; // 30 graus
	this->fConstantAttenuation  = 1.0f;
	this->fLinearAttenuation    = 0.0f;
	this->fQuadraticAttenuation = 0.0f;
	this->iLightSourceIndex     = uiIndex;
}
/**
  \brief Construtor de clonagem para a classe LightSource
  Cria uma copia exata de um objeto fonte de luz ja existente
  \param uiIndex indice da fonte de luz a ser criada (valores validos 0-7)
  \param clone Objeto a ser clonado
*/
LightSource::LightSource( unsigned int uiIndex, const LightSource& clone ) : ColoredEntity( clone )
{
	this->Type                  = clone.Type;
	this->bActive               = clone.bActive;
	this->vAmbientColor         = clone.vAmbientColor;
	this->vSpecularColor        = clone.vSpecularColor;
	this->vDirection            = clone.vDirection;
	this->fExponent             = clone.fExponent;
	this->fCuttOff              = clone.fCuttOff;
	this->fConstantAttenuation  = clone.fConstantAttenuation;
	this->fLinearAttenuation    = clone.fLinearAttenuation;
	this->fQuadraticAttenuation = clone.fQuadraticAttenuation;
	this->iLightSourceIndex     = uiIndex;
}
/**
  \brief Construtor de clonagem para a classe LightSource a partir de ponteiros
  Cria uma copia exata de um objeto fonte de luz ja existente
  \param uiIndex indice da fonte de luz a ser criada (valores validos 0-7)
  \param ptrClone ponteiro para um objeto a ser clonado
*/
LightSource::LightSource( unsigned int uiIndex, LightSource* ptrClone ) : ColoredEntity( ptrClone )
{
	this->Type                  = ptrClone->Type;
	this->bActive               = ptrClone->bActive;
	this->vAmbientColor         = ptrClone->vAmbientColor;
	this->vSpecularColor        = ptrClone->vSpecularColor;
	this->vDirection            = ptrClone->vDirection;
	this->fExponent             = ptrClone->fExponent;
	this->fCuttOff              = ptrClone->fCuttOff;
	this->fConstantAttenuation  = ptrClone->fConstantAttenuation;
	this->fLinearAttenuation    = ptrClone->fLinearAttenuation;
	this->fQuadraticAttenuation = ptrClone->fQuadraticAttenuation;
	this->iLightSourceIndex     = uiIndex;
}
/**
  \brief Especifica o valor da constante de iluminacao ambiente da fonte de luz
  \param vColor cor da iluminacao ambiente da fonte de luz
*/
void LightSource::setAmbientColor( Vector3 vColor )
{
	this->vAmbientColor = vColor;
}
/**
  \brief Especifica o valor da constante de iluminacao especular da fonte de luz
  \param vColor cor da iluminacao especular da fonte de luz
*/
void LightSource::setSpecularColor( Vector3 vColor )
{
	this->vSpecularColor = vColor;
}
/**
  \brief Especifica o valor da direcao do feixe de iluminacao direcional (ou spot) da fonte de luz
  \param vDirection direcao principal do eixo do feixe de iluminacao da fonte de luz
*/
void LightSource::setDirection( Vector3 vDirection )
{
	this->vDirection = vDirection;
}
/**
  \brief Especifica o valor da constante expoente para o calculo da iluminacao spot da fonte de luz
  \param fValue valor do expoente no calculo da iluminacao spot
*/
void LightSource::setExponent( float fValue )
{
	this->fExponent = fValue;
}
/**
  \brief Especifica o valor do angulo de abertura do feixe de iluminacao spot da fonte de luz
  \param fAngle angulo de abertura do feixe de iluminacao spot
*/
void LightSource::setCutOff( float fAngle )
{
	this->fCuttOff = fAngle;
}
/**
  \brief Especifica o valor do fator de atenuacao da fonte de luz pela distancia de forma constante
  \param fFactor fator de atenuacao da luz
*/
void LightSource::setConstantAttenuation( float fFactor )
{
	this->fConstantAttenuation = fFactor;
}
/**
  \brief Especifica o valor do fator de atenuacao da fonte de luz pela distancia de forma linear
  \param fFactor fator de atenuacao da luz
*/
void LightSource::setLinearAttenuation( float fFactor )
{
	this->fLinearAttenuation = fFactor;
}
/**
  \brief Especifica o valor do fator de atenuacao da fonte de luz pela distancia de forma quadratica
  \param fFactor fator de atenuacao da luz
*/
void LightSource::setQuadraticAttenuation( float fFactor )
{
	this->fQuadraticAttenuation = fFactor;
}
/**
	\brief Ativa/desativa a luz
*/
void LightSource::Activate()
{
	this->bActive = !this->bActive;

	if( this->bActive )
		glEnable( lightENUM );
	else
		glDisable( lightENUM );
}
/**
   \brief Rotina de desenho da fonte de luz no OPENGL
*/
void LightSource::OnRender()
{
	switch( this->iLightSourceIndex )
	{
	case 0: lightENUM = GL_LIGHT0; break;
	case 1: lightENUM = GL_LIGHT1; break;
	case 2: lightENUM = GL_LIGHT2; break;
	case 3: lightENUM = GL_LIGHT3; break;
	case 4: lightENUM = GL_LIGHT4; break;
	case 5: lightENUM = GL_LIGHT5; break;
	case 6: lightENUM = GL_LIGHT6; break;
	case 7: lightENUM = GL_LIGHT7; break;
	}

	if( this->Type == LightSource::DIRECTIONAL )
	{
		float vec[4] = { this->vDirection.x, this->vDirection.y, this->vDirection.z,  0.0f };
		glLightfv( lightENUM, GL_POSITION, vec );
	}
	else
	{
		float vec[4] = { this->vTranslate.x, this->vTranslate.y, this->vTranslate.z, 1.0f };
		glLightfv( lightENUM, GL_POSITION, vec );

		if( this->Type == LightSource::SPOTLIGHT )
		{
			float dir[4] = { this->vDirection.x, this->vDirection.y, this->vDirection.z,  1.0f };
			glLightfv( lightENUM, GL_SPOT_DIRECTION, dir );

			glLightf( lightENUM, GL_SPOT_EXPONENT, this->fExponent );
			glLightf( lightENUM, GL_SPOT_CUTOFF, this->fCuttOff );
		}
	}

	float amb[4] = { this->vAmbientColor.x, this->vAmbientColor.y, this->vAmbientColor.z, this->vAmbientColor.w };
	glLightfv( lightENUM, GL_AMBIENT, amb );

	float dif[4] = { this->vColor.x, this->vColor.y, this->vColor.z, this->vColor.w };
	glLightfv( lightENUM, GL_DIFFUSE, dif );

	float spec[4] = { this->vSpecularColor.x, this->vSpecularColor.y, this->vSpecularColor.z, this->vSpecularColor.w };
	glLightfv( lightENUM, GL_SPECULAR, spec );

	glLightf( lightENUM, GL_CONSTANT_ATTENUATION, this->fConstantAttenuation );
	glLightf( lightENUM, GL_LINEAR_ATTENUATION, this->fLinearAttenuation );
	glLightf( lightENUM, GL_QUADRATIC_ATTENUATION, this->fQuadraticAttenuation );

	if( this->bActive )
		glEnable( lightENUM );
	else
		glDisable( lightENUM );
}
/**
	\brief Rotina de atualizacao dos parametros animaveis desse objeto.
	\param dDeltaTime intervalo de tempo transcorrido desde a ultima atualizacao.
*/
void LightSource::OnLoop( double dDeltaTime )
{
	if( this->ptrKeyframing )
	{
		Pose * ptrCurrentPose = NULL;
		if( ptrCurrentPose = this->ptrKeyframing->OnLoop( dDeltaTime ) )
		{
			if( ptrCurrentPose->hasPoseAttributeName( "ambient" ) )
				this->setAmbientColor( (( VectorAttribute * ) ptrCurrentPose->getPoseAttribute( "ambient" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "diffuse" ) )
				this->setColor( (( VectorAttribute * ) ptrCurrentPose->getPoseAttribute( "diffuse" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "specular" ) )
				this->setSpecularColor( (( VectorAttribute * ) ptrCurrentPose->getPoseAttribute( "specular" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "exponent" ) )
				this->setExponent( (( FloatAttribute * ) ptrCurrentPose->getPoseAttribute( "exponent" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "cut off" ) )
				this->setCutOff( (( FloatAttribute * ) ptrCurrentPose->getPoseAttribute( "cut off" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "constant attenuation" ) )
				this->setConstantAttenuation( (( FloatAttribute * ) ptrCurrentPose->getPoseAttribute( "constant attenuation" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "linear attenuation" ) )
				this->setLinearAttenuation( (( FloatAttribute * ) ptrCurrentPose->getPoseAttribute( "linear attenuation" ) )->getValue() );

			if( ptrCurrentPose->hasPoseAttributeName( "quadratic attenuation" ) )
				this->setQuadraticAttenuation( (( FloatAttribute * ) ptrCurrentPose->getPoseAttribute( "quadratic attenuation" ) )->getValue() );
		}
	}
	ColoredEntity::OnLoop( dDeltaTime );
}
