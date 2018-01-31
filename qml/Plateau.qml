import QtQuick 2.7
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

Grid {
    id: grid

    // distance par rapport au haut de la fenetre
    anchors.centerIn: parent
    // regarde la taille de ApplicationWindow et centre notre grille sur la valeur horizontale

    property int size: 5
    //declaration d'une propriété
    rows: size
    // declaration du nombre de ligne
    columns: size
    // déclaration du nombre de colonne


    Repeater {

        model:(typeof modele2048 === "undefined")? "" : modele2048

        delegate: Rectangle {
            width: 80  * root.responsive
            height: width
            radius: 10
            border.color: "#3399ff"
            border.width: 3
            color: "#cbbeb1"

            Text {
                id: texte
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: parent.height / ( 1 + ( text.length  ) )

                text:  modele2048[index]

                onTextChanged : {
                    Context.game2048


                    var valueInCase = texte.text *1 ;


                    switch(valueInCase) {
                    case 0:
                        texte.text = "";
                        break;
                    case 2:
                        parent.color = "mediumpurple";//"#D4E0F7";
                        break;
                    case 4:
                        parent.color = "darkviolet";//#1258DC";
                        break;
                    case 8:
                        parent.color = "royalblue";//"#EA202C";
                        break;
                    case 16:
                        parent.color = "deepskyblue";//"#FDED2A";
                        break;
                    case 32:
                        parent.color = "cyan";
                        break;
                    case 64:
                        parent.color = "lime";
                        break;
                    case 128:
                        parent.color = "greenyellow";
                        break;
                    case 256:
                        parent.color = "yellow";
                        break;
                    case 512:
                        parent.color = "orange";
                        break;
                    case 1024:
                        parent.color = "orangered";
                        break;
                    case 2048:
                        parent.color = "red";
                        break;
                    case 4096:
                        parent.color = "firebrick";
                        break;
                    case 8192:
                        parent.color = "chocolate";
                        break;
                    default:
                        parent.color = "burlywood";
                        break;
                    }
                }
            }
        }
    }
}
