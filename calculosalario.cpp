#include "calculosalario.h"

float CalculoSalario::SalarioBruto() const
{
    return m_salarioBruto;
}

float CalculoSalario::descuento() const
{
    return m_descuento;
}

float CalculoSalario::salarioNeto() const
{
    return m_salarioNeto;
}

float CalculoSalario::getSalarioBruto() const
{
    return m_salarioBruto;
}

float CalculoSalario::getDescuento() const
{
    return m_descuento;
}

float CalculoSalario::getSalarioNeto() const
{
    return m_salarioNeto;
}

QString CalculoSalario::getJornada()
{
    switch (m_jornada) {
    case 'V':
        return "Vespertina";
        break;
    case 'N':
        return "Nocturna";
        break;
    case 'M':
        return "Matutina";
        break;
    }
    return "N/D";
}

CalculoSalario::CalculoSalario(QObject *parent) : QObject (parent)
{

}

CalculoSalario::CalculoSalario(QString nombre, int horas, char jornada)
{
    this->m_nombre=nombre;
    this->m_horas=horas;
    this->m_jornada =jornada;
}

void CalculoSalario::calcular()
{
    float valorHora = 0;
    switch (this->m_jornada) {
        case 'V':
                valorHora = Valor_Hora_Vespertino;
        break;
        case 'M':
            valorHora = Valor_Hora_Matutino;
        break;
        case 'N':
            valorHora = Valor_Hora_Nocturno;
        break;
    }
    this->m_salarioBruto= this->m_horas *valorHora;
    this->m_descuento = this->m_salarioBruto * this->Porcentaje_Descuento/100;
    this->m_salarioNeto = this->m_salarioBruto-this->m_descuento;
}

QString CalculoSalario::resultado()
{
    QString str ="Obrero: "+this->m_nombre+"\n";
            str+="Horas: "+QString::number(this->m_horas)+"\n";
            str+="Jornada: "+getJornada()+'\n';
            str+="Salario Bruto: $"+QString::number(this->m_salarioBruto)+"\n";
            str+="Descuento: $"+QString::number(this->m_descuento)+"\n";
            str+="Salario Neto: $"+QString::number(this->m_salarioNeto)+"\n\n";
    return str;
}

