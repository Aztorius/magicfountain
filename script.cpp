#include "script.h"

Script::Script(QString script)
{
    QStringList lines = script.split("\n");
    QString text;

    QString content = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">";
    content.append("<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">");
    content.append("p, li { white-space: normal; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; }");
    content.append("</style></head><body>");

    int blockcount = lines.size();
    int i = 0;

    while(i < blockcount){
        text = lines.at(i).trimmed();

        if(text.left(1) == "!"){ //Forced action
            content.append("<p>" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
        }
        else if(text.left(2) == "= "){ //Synopses
            //Not used yet
        }
        else if(text.left(6) == "Title:"){ //Title
            content.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(6).trimmed()));
            title.append(text.mid(6).trimmed());
            i++;
            text = lines.at(i);

            while(text.left(1) == "\t" && i < blockcount){
                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));
                title.append(text.trimmed());

                i++;
                text = lines.at(i);
            }
            i--;
            content.append("<br/></p>");
        }
        else if(text.left(7) == "Credit:"){ //Credit
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()) + "</p>");
        }
        else if(text.left(7) == "Author:"){ //Author
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()) + "<br/></p>");
        }
        else if(text.left(7) == "Source:"){ //Source
            content.append("<p style=\"text-align: center;\">" + checkBoldItalicUnderline(text.mid(7).trimmed()) + "<br/></p>");
        }
        else if(text.left(11) == "Draft date:"){ //Draft date
            content.append("<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><p style=\"text-align: left;\">" + checkBoldItalicUnderline(text.mid(11).trimmed()) + "</p>");
        }
        else if(text.left(8) == "Contact:"){ //Contact
            content.append("<p style=\"text-align: left;\">" + checkBoldItalicUnderline(text.mid(8).trimmed()));
            contact.append(text.mid(8).trimmed());

            i++;
            text = lines.at(i);

            while(text.left(1) == "\t" && i < blockcount){
                content.append("<br/>" + checkBoldItalicUnderline(text.trimmed()));

                i++;
                text = lines.at(i);
            }
            i--;
            content.append("<br/></p>");
        }
        else if(text.left(4) == "### "){ //Scene
            //Not used yet
        }
        else if(text.left(3) == "## "){ //Sequence
            //Not used yet
        }
        else if(text.left(2) == "# "){ //Act
            //Not used yet
        }
        else if(text.left(3).toLower() == "int" || text.left(3).toLower() == "ext" || text.left(8).toLower() == "int./ext" || text.left(7).toLower() == "int/ext" || text.left(3).toLower() == "i/e"){ //Scene heading
            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if(text.left(1) == ">"){
            if(text.right(1) == "<"){ //Centered
                content.append("<p style=\"text-align:center;\">" + checkBoldItalicUnderline(text.mid(1, text.size()-2)) + "</p>");
            }
            else if(text.toUpper() == text){ //Transition
                content.append("<p style=\"margin-left: 384px;\">" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
            }
        }
        else if(text.right(3) == "TO:" && text.toUpper() == text){ //Transition
            content.append("<p style=\"margin-left: 384px;\">" + checkBoldItalicUnderline(text) + "</p>");
        }
        else if(text.left(1) == "." && text.mid(1, 1) != "."){ //Forced scene heading
            content.append("<p>" + checkBoldItalicUnderline(text.mid(1)) + "</p>");
        }
        else if(text.toUpper() == text && !text.isEmpty()){ //Dialogue
            content.append("<p style=\"margin-left: 192px;\">" + checkBoldItalicUnderline(text) + "</p>"); //Character name : 2 inches from left side
            i++;

            if(i >= blockcount){
                break;
            }

            text = lines.at(i).trimmed();

            while(!text.isEmpty() && i < blockcount){

                if(text.left(1) == "(" && text.right(1) == ")"){ //Parenthetical : 1.5 inches from left side
                    content.append("<p style=\"margin-left: 144px; margin-right: 192px;\">" + checkBoldItalicUnderline(text) + "</p>");
                }
                else if(!text.isEmpty()){ //Dialogue : 1 inche from left side
                    content.append("<p style=\"margin-left: 96px; margin-right: 144px;\">" + checkBoldItalicUnderline(text) + "</p>");
                }

                i++;

                if(i >= blockcount){
                    break;
                }

                text = lines.at(i).trimmed();
            }

            i--;
        }
        else if(!lines.at(i).isEmpty()){ //Default action
            text = lines.at(i);

            content.append("<p>" + checkBoldItalicUnderline(text) + "</p>");
        }
        else{ //Blank action
            text = lines.at(i);
            content.append("<p style=\"white-space:pre-warp;\"> </p>"); //Add blank line
        }

        i++;
    }

    content.append("</body></html>");

    htmlScript = content;
}

QString Script::checkBoldItalicUnderline(QString text){
    QString result = text;

    //Check Bold with Italic, ex: ***something***
    while(result.contains("***") && result.mid(result.indexOf("***") + 3).contains("***")){
        result.replace(result.indexOf("***"), 3, "<b><i>");
        result.replace(result.indexOf("***"), 3, "</i></b>");
    }

    //Check Bold, ex: **something**
    while(result.contains("**") && result.mid(result.indexOf("**") + 2).contains("**")){
        result.replace(result.indexOf("**"), 2, "<b>");
        result.replace(result.indexOf("**"), 2, "</b>");
    }

    //Check Italic, ex: *something*
    while(result.contains("*") && result.mid(result.indexOf("*") + 1).contains("*")){
        result.replace(result.indexOf("*"), 1, "<i>");
        result.replace(result.indexOf("*"), 1, "</i>");
    }

    //Check Underline, ex: _something_
    while(result.contains("_") && result.mid(result.indexOf("_") + 1).contains("_")){
        result.replace(result.indexOf("_"), 1, "<u>");
        result.replace(result.indexOf("_"), 1, "</u>");
    }

    return result;
}

QString Script::toHtml(){
    return htmlScript;
}
