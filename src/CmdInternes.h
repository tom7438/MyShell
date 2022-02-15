#ifndef __CMDINTERNES_H
#define __CMDINTERNES_H

/* Fonction qui permet de savoir si la chaîne de caractères donnée en argument est une commande interne
 * Valeur de retour : 0 si commande interne, -1 sinon
 */
int searchCmd(char *cmd);

/* Fonction qui appelle la commande interne
 * Valeur de retour : 0 si tout s'est bien passé, -1 sinon
 */
int cmd(char **cmd);

/* Fonction pwd interne
 *
 */
void cmdPwd();

#endif