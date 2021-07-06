#ifndef CALCULOSALARIO_H
#define CALCULOSALARIO_H

#include <QObject>

class CalculoSalario:public QObject
{
    Q_OBJECT
    Q_PROPERTY(float SalarioBruto READ SalarioBruto)
    Q_PROPERTY(float descuento READ descuento)
    Q_PROPERTY(float salarioNeto READ salarioNeto)
private:
    /*Constantes */
    float const Valor_Hora_Matutino= 5.15;
    float const Valor_Hora_Vespertino= 8.5;
    float const Valor_Hora_Nocturno= 12.65;
    float const Porcentaje_Descuento= 9.5;
    /*Variables Miembro*/
    int m_horas;    //Numero de horas trabajadas
    QString m_nombre;//Nombre del trabajador
    char m_jornada; //jornada que trabaja [V=Vespertina,M=Matutina,N=nocturno]

    float m_salarioBruto;   //valor de salario sin descuento
    float m_descuento;      //valor del descuento
    float m_salarioNeto;    // valor del salario a recibir
    QString getJornada();
public:
    explicit CalculoSalario(QObject *parent=nullptr);
    CalculoSalario(QString nombre,int horas,char jornada);
    void calcular();
    QString resultado();

    float SalarioBruto() const;
    float descuento() const;
    float salarioNeto() const;
    /*Obtener datos*/
    float getSalarioBruto() const;
    float getDescuento() const;
    float getSalarioNeto() const;
};

#endif // CALCULOSALARIO_H
