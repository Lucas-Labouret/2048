#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

/**Sauvegarde la partie dansun fichier savefile.txt
 * @param seed la seed utilisée par la fonction srand() en début de partie
 * @param gridHistory l'historique des plateau générés durant la partie
**/
void saveFile(int seed, vector<matrix> gridHistory);
/**Charge une partie sauvergdée dans un fichier savefile.txt
**/
vector<matrix> loadFile();
