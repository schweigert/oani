/**
   \file Animator.h
   \brief Descricao da classe Animator

   Esta classe tem por objetivo implementar a animação pose-to-pose

   Desenvolvido por Rogerio Eduardo da Silva<br>
   Março, 2017. Universidade do Estado de Santa Catarina - UDESC<br>
*/
#ifndef _ANIMATOR_NOT_INCLUDED_
#define _ANIMATOR_NOT_INCLUDED_

#include "Entity.h"
#include "Interpolator.h"

#include <vector>
using namespace std;

/**
   \class Animator
   \brief Classe que implementa uma animação pose-to-pose com base em uma serie de interpoladores
   \sa Interpolator
*/
class Animator
{
public:
	/**
	\brief Lista de possiveis tipos de animações suportados
	*/
	enum AnimationType {
		ONCE = 0,  ///< execute a linha de tempo uma vez e para o processo de animação
		LOOP       ///< executa o processo de animação de forma ciclica
	};

protected:
    Entity *              ptrOwner;            ///< ponteiro para o objeto que sera afetado por este Animator
    AnimationType         animationType;       ///< tipo de animação executada por este animador
    double                dAnimationTime;      ///< tempo acumulado deste o inicio do processo de animação
    vector<Interpolator*> listOfInterpolators; ///< lista de interpoladores que compoem esta animação

public:
    Animator( Animator::AnimationType = Animator::ONCE );
    Animator( const Animator & );
    Animator( Animator * );
    ~Animator();

    void setParent( Entity* );

    void OnLoop( double );

    void addInterpolator( Interpolator * );

};

#endif

