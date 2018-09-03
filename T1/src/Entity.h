/**
   \file Entity.h
   \brief Descricao da classe Entity

   Esta classe tem por objetivo agrupar todos os elementos do
   framework que compartilhem atributos geometricos como translacao, rotacao e
   escala.<br>

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Agosto, 2013. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _ENTITY_NOT_INCLUDED_
#define _ENTITY_NOT_INCLUDED_

#include "Vector3.h"

/**
   \class Entity
   \brief Classe que tem por objetivo agrupar todos os elementos espaciais que compoem a cena sendo animada.
*/
class Entity
{
protected:
	Vector3 vTranslate, ///< vetor translacao em coordenadas locais
	   		vRotate, 	///< angulos de rotacao em relacao a cada eixo cartesiano
			vScale; 	///< fatores de escala em relacao a cada eixo cartesiano
    Vector3 vPivot;		///< vetor pivot

public:
		Entity();
		Entity( const Entity& );
	   	Entity( Entity* );

	   	void setTranslate( Vector3 );
	   	void setRotate( Vector3 );
	   	void setScale( Vector3 );
        void setPivot( Vector3 );

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
		  \brief Retorna o valor corrente do tamanho do objeto
		  \return Vector3 com o valor atual do vetor escala
		*/
	    inline Vector3 getPivot() { return this->vPivot; }
		/**
		  \brief Rotina de renderizacao do objeto em OPENGL.<p>Esta rotina deve
		  ser sobrecarregada para cada tipo de entidade em particular.
		*/
	    virtual void OnRender() = 0; // metodo abstrato: precisa ser implementado em uma classe-filha
		/**
		  \brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
		  Esta rotina deve ser sobrecarregada para cada tipo de entidade em
		  particular.
		*/
	    virtual void OnLoop( double ) = 0; // metodo abstrato: precisa ser implementado em uma classe-filha

};

#endif
