
#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector3.h"
#include "Keyframing.h"

/**
   \class Entity
   \brief Classe que tem por objetivo agrupar todos os elementos espaciais que compoem a cena sendo animada.
*/
class Entity
{
protected:
	   Vector3          vTranslate,     ///< vetor translacao em coordenadas locais
	   		            vRotate,        ///< angulos de rotacao em relacao a cada eixo cartesiano
			            vScale;         ///< fatores de escala em relacao a cada eixo cartesiano
	   Keyframing *     ptrKeyframing;  ///< ponteiro para objeto de animacao keyframing (pose-to-pose)
	   vector<Entity*>  listOfEntities; ///< lista de objetos Entity associados a este pivot

public:
	   Entity();
	   Entity( const Entity& );
	   Entity( Entity* );
	   ~Entity();

	   void setTranslate( Vector3 );
	   void setRotate( Vector3 );
	   void setScale( Vector3 );

	   void attach( Entity* );
	   Entity* getChild( unsigned int );
	   /**
	     \brief Retorna a quantidade de entidades filhas deste objeto
		 \return a quantidade de filhos desta entidade
	   */
	   unsigned int getNumOfChilds() { return ( unsigned int ) this->listOfEntities.size(); }

	   void setKeyframing( Keyframing* );
	   /**
	     \brief Retorna o ponteiro para o objeto Keyframing corrente
		 \return ponteiro para o objeto de animacao Pose-to-Pose
	   */
	   inline Keyframing* getKeyframing() { return this->ptrKeyframing; }

		/**
		  \brief Retorna o valor corrente da posicao do objeto
		  \return Vector3 com o valor atual do vetor translacao
		*/
	   inline Vector3 getTranslate() { return this->vTranslate; }
		/**
		  \brief Retorna o valor corrente da orientacao do objeto
		  \return Vector3 com o valor atual do vetor rotacao
		*/
	   inline Vector3 getRotate() { return this->vRotate; }
		/**
		  \brief Retorna o valor corrente do tamanho do objeto
		  \return Vector3 com o valor atual do vetor escala
		*/
	   inline Vector3 getScale() { return this->vScale; }
		/**
		  \brief Rotina de renderizacao do objeto em OPENGL.<p>Esta rotina deve
		  ser sobrecarregada para cada tipo de entidade em particular.
		*/
	   virtual void OnRender();
	   virtual void OnLoop( double );
};

#endif
