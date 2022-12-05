#include "citoyen.h"

citoyen::citoyen()
{

    cin="";
    prenom="";
    nom="";
    adress="";
    email="";
    num="";
    type="";
    plus="";
    nomct="";
    prenomct="";
    id="";
    date="";


    }

    void citoyen::setcin(QString n){cin=n;}
    void citoyen::setnom(QString n){nom=n;}
    void citoyen::setprenom(QString n){prenom=n;}
    void citoyen::setadress(QString n){adress=n;}
    void citoyen::setemail(QString n){email=n;}
    void citoyen::setnum(QString n){num=n;}
    void citoyen::setype(QString n){type=n;}
    void citoyen::setplus(QString n){plus=n;}
    void citoyen::setnomct(QString n){nomct=n;}
    void citoyen::setprenomct(QString n){prenomct=n;}
    void citoyen::setid(QString n){id=n;}
    void citoyen::setdate(QString n){date=n;}


    QString citoyen::get_nom(){return nom;}
    QString citoyen::get_prenom(){return prenom;}
    QString citoyen::get_cin(){return cin;}
    QString citoyen::get_adress(){return adress;}

    QString citoyen::get_num(){return num;}
    QString citoyen::get_email(){return email;}
    QString citoyen::get_type(){return type;}
    QString citoyen::get_plus(){return plus;}
    QString citoyen::get_nomct(){return nomct;}
    QString citoyen::get_prenomct(){return prenomct;}
    QString citoyen::get_date(){return date;}




    bool citoyen::ajouter(){

        QSqlQuery query;
        query.prepare("insert into CITOYEN(ID_CT,NOM_CT,PRENOM_CT,ADRESS_CT,MAIL_CT,NUM_CT,TYPE_CT,PLUS_CT)" "values(:cin, :nom, :prenom, :adress, :mail, :num, :type, :plus)");
        query.bindValue(":cin",cin);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":adress",adress);
        query.bindValue(":mail",email);
        query.bindValue(":num",num);
        query.bindValue(":type",type);
        query.bindValue(":plus",plus);
        return query.exec();
    }

    bool citoyen::suprimer(int cin)
    {
        QSqlQuery query,qry;
        QString res=QString::number(cin);
        if(res=="0"){qry.prepare("delete from  DATE_CT ");
            query.prepare("delete from  CITOYEN ");
        }
        else{
            qry.prepare("delete from DATE_CT where CIT_ID= :cin");
        query.prepare("delete from CITOYEN where ID_CT= :cin");

        query.bindValue(":cin",res);


        }
        return (query.exec()&&qry.exec());

    }

    QSqlQueryModel * citoyen::afficher()
    {
        QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select * from CITOYEN");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("adress"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("numero de telephone"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("la tribu"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("l'evidance"));
        return model;


    }
    QSqlQueryModel* citoyen::recherche(QString chaine_search,QString variable)

    {
        QSqlQueryModel* model=new QSqlQueryModel();
        QSqlQuery query;
        if(variable=="ID_CT")
         {
         model->setQuery("SELECT * FROM CITOYEN WHERE  (ID_CT like '"+chaine_search+"%""')  ");
         }
        if(variable=="NOM_CT")
         {
         model->setQuery("SELECT * FROM CITOYEN WHERE  (NOM_CT like '"+chaine_search+"%""')  ");  //CHAINE ELI NEKTEB FEHA FEL LINE EDIT
         }
        if(variable=="PRENOM_CT")
         {
         model->setQuery("SELECT * FROM CITOYEN WHERE  (PRENOM_CT like '"+chaine_search+"%""')  ");  //CHAINE ELI NEKTEB FEHA FEL LINE EDIT
         }
        if(variable=="ADRESS_CT")
         {
         model->setQuery("SELECT * FROM CITOYEN WHERE  (ADRESS_CT like '"+chaine_search+"%""')  ");
         }
        if(variable=="MAIL_CT")
         {
         model->setQuery("SELECT * FROM CITOYEN WHERE  (MAIL_CT like '"+chaine_search+"%""')  ");
         }
        if(variable=="NUM_CT")
         {
         model->setQuery("SELECT * FROM CITOYEN WHERE  (NUM_CT like '"+chaine_search+"%""')  ");
         }

        model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("adress"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Email"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("numero de telephone"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("la tribu"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("l'evidance"));



            return  model;
    }


    bool citoyen::update(QString id,QString adrss,QString mail,QString numr)
    {

      QSqlQuery query;
      query.prepare("update CITOYEN set ADRESS_CT='"+adrss+"' ,MAIL_CT='"+mail+"', NUM_CT='"+numr+"' where ID_CT='"+id+"' " );
      return query.exec();
    }
    QSqlQueryModel* citoyen::trier(){
        QString sQuery="SELECT ID_CT,NOM_CT,PRENOM_CT,ADRESS_CT,MAIL_CT,NUM_CT,TYPE_CT,PLUS_CT FROM CITOYEN ORDER BY ID_CT";

        QSqlQueryModel*model3=new QSqlQueryModel();

        QSqlQuery qry;

        qry.prepare(sQuery);

        qry.exec();
        model3->setQuery(qry);
    return model3
            ;}
    bool citoyen::ajoutert(QString idd,QString datet){

        QSqlQuery query;
        query.prepare("insert into DATE_CT(CIT_ID,DATES_CT)" "values(:id, :date)");
        query.bindValue(":id",idd);
        query.bindValue(":date",datet);
        return query.exec();
    }


