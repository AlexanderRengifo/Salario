#include "principal.h"
#include "ui_principal.h"
Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    //conectar obejtos
    /*connect(ui->actionCalcular,SIGNAL(triggered()),
            this,SLOT(on_cmdCalcular_clicked()));*/
    /**leer un archivo**/

    //direccion del archivo
    /*QFile f("C:/Users/alexr/OneDrive - Universidad Politecnica Salesiana/Desktop/salarios2021.text");
    //creando fichero
    QTextStream in (&f);
    //si no se puede abrir el archivo mostrar que el archivo no se abrio y retornara
    if(!f.open(QIODevice::ReadOnly)){
        qDebug()<<"No se puede abrir el archivo";
        return;
    }
    //imprime el archivo
    while (!in.atEnd()) {
        qDebug("%s",qPrintable(in.readLine()));
    }
    f.close();*/
}

Principal::~Principal()
{
    delete ui;
}
void Principal::on_actionSalir_triggered()
{
    this->close();
}


void Principal::on_cmdCalcular_clicked()
{
    this->calcular();
}

void Principal::on_actionCalcular_triggered()
{
    this->calcular();
}

void Principal::calcular()
{
    //obtener el nombre
    QString nombre = ui->inNombre->text();

    //valida que el nombre no este vacio
    if(nombre.isEmpty()){
        QMessageBox::warning(this, "Salarios","No has proporcionado el nombre del obrero");
        return;
    }
    //obtiene horas
    int horas = ui->inHoras->value();
    //obtiene la jornada
    char jornada = '\0';
    if(ui->inMatutina->isChecked()){
        jornada ='M';
    }else if (ui->inNocturna->isChecked()){
        jornada ='N';
    }else if(ui->inVespertina->isChecked()){
        jornada ='V';
    }
    //Instancia el bojeto y se calcula
    CalculoSalario *s1 = new CalculoSalario(nombre,horas,jornada);
    s1->calcular();
    //muestro resultados
    ui->outResultado->appendPlainText(s1->resultado());
    //encerar los widgets
    this->borrar();
}

void Principal::borrar()
{
    ui->inNombre->setText("");
    ui->inHoras->clear();
    ui->inMatutina->setChecked(true);
    ui->inNombre->setFocus();
}

void Principal::nuevo()
{
    ui->outResultado->clear();
}

void Principal::on_actionNuevo_triggered()
{
    this->nuevo();
}

void Principal::on_actionAcerca_de_triggered()
{
    Acerca *acercaDE=new Acerca(this);
    acercaDE->setVersion(VERSION);
    acercaDE->show();
}

void Principal::on_actionGuardar_triggered()
{
    //crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();
    // agregar el path absoluto del objetos , un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath()+"/sin_nombre.txt";
    //abrir un cuadro de dialogo para seleccionar el nombre y el archivo a guardar
    QString fileName = QFileDialog::getSaveFileName(this,"Guardar Archivo",
                                                    pathArchivo,
                                                    "Archivo de texto(*.text)");
    ///guardar datos en el archivo
    //crear el archivo a partir del nombre arrojado por el cuadro de dialogo
    QFile f(fileName);
    //crear el objeto QTextStream(permite escribir el archivo)
    QTextStream out(&f);
    //intentar abrir el archivo ya sea para escibirlo o para agregar texto si existiera
    if(!f.open(QIODevice::WriteOnly|QIODevice::Append)){
        //si no se puede abrir muestra un mensaje de adrvertencia
        QMessageBox::warning(this,"Salarios","No se puede abrir el archivos"+fileName);
        //salir de la funcion
        return;

    }
    //guardar contenido del texto de resultado en el archivo
    out<<ui->outResultado->toPlainText()<<endl;
    //cerrar el archivoi
    f.close();
    //mostrar mensaje en la barra de estados
    ui->statusbar->showMessage("Archivo guradado en " + fileName,3000);
}

void Principal::on_actionAbrir_triggered()
{
    //crear un objeto QDir a partir del directorio del usuario
    QDir directorio = QDir::home();
    // agregar el path absoluto del objetos , un nombre por defecto del archivo
    QString pathArchivo = directorio.absolutePath()+"/sin_nombre.txt";
    //abrir un cuadro de dialogo para seleccionar el archivo que queremos abrir
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir Archivo",
                                                    pathArchivo,
                                                    "Archivo de texto(*.text)");
    //creando direccion del archivos
    QFile f(fileName);
    //creando fichero
    QTextStream in (&f);
    //mostramos un mensaje de adevertencia en caso de que no se pueda abrir el archivo
    if(!f.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this,"Salarios","No se puede abrir el archivos"+fileName);
        return;
    }

    QString str;
    //guardamos todo el archivo de texto en la variable str
    while (!in.atEnd()) {
        str+=(in.readLine()+"\n");//lee linea por linea y la aumenta en str y por cada linea da un salto de linea para ordenar el archivo de texto
    }
    //añadimos al ouResultado todo lo que guardamos en la variable str
    ui->outResultado->appendPlainText(str);
    //cerramos nuestro archivos
    f.close();
    //mostramos en el cuadro de estado durante 3 segundos que el archivo fue abierto
    ui->statusbar->showMessage("Archivo abierto ",3000);
}
