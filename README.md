# 🔐 Smart House Lock – Serrure intelligente à code

Prototype de serrure électronique à mot de passe, réalisé sur **Arduino UNO** dans le cadre du module *Projet électronique* à l'ENSTTIC (Oran).

Projet réalisé en binôme avec **Sara Bouazza**.

![Schéma du circuit (Tinkercad)](images/schema-circuit-tinkercad.png)

## Fonctionnement

- Saisie d'un code de **4 caractères** au clavier matriciel 4x4, affiché sous forme d'astérisques sur l'écran LCD ; la touche `#` valide le code.
- **Code utilisateur correct** : l'écran affiche « Welcome », le servomoteur s'ouvre (90°), puis la serrure se referme automatiquement après **5 secondes**.
- **Code incorrect** : l'écran affiche « Repeat » et le buzzer émet un bip court.
- **3 échecs consécutifs** : l'alarme se déclenche (« ALARME ACTIVE », bip répété toutes les secondes).
- **Désactivation de l'alarme** : saisie du code utilisateur ou du code maître, l'écran affiche « Alarme OFF ».

> Les codes présents dans le programme (utilisateur et maître) sont des codes de démonstration.

## Matériel

| Composant | Rôle |
|---|---|
| Arduino UNO (ATmega328P) | Microcontrôleur |
| Clavier matriciel 4x4 | Saisie du code |
| Écran LCD 16x2 I2C (adresse `0x27`) | Affichage des messages |
| Servomoteur | Simulation du verrou |
| Buzzer | Alertes sonores |
| Breadboard et fils | Câblage |

## Branchements

| Élément | Broches Arduino |
|---|---|
| Clavier, lignes | 9, 8, 7, 6 |
| Clavier, colonnes | 5, 4, 3, 2 |
| Servomoteur | 10 |
| Buzzer | 13 |
| LCD I2C | SDA / SCL |

## Bibliothèques Arduino

`Servo` · `Keypad` · `Wire` · `LiquidCrystal_I2C`

## Utilisation

1. Ouvrir `smart_house_lock.ino` dans l'IDE Arduino.
2. Installer les bibliothèques **Keypad** et **LiquidCrystal I2C** (Gestionnaire de bibliothèques).
3. Téléverser le programme sur la carte, ou simuler le montage sur Tinkercad Circuits.

## Pistes d'amélioration

- Remplacer l'attente bloquante (`delay`) de l'alarme par une gestion non bloquante.
- Stocker les codes en mémoire EEPROM pour pouvoir les modifier sans reprogrammer la carte.
- Ajouter un journal des tentatives et une connexion sans fil.

## Documentation

Rapport complet : [docs/rapport-smart-locking-system.docx](docs/rapport-smart-locking-system.docx)

## Auteures

Farah Bounouara et Sara Bouazza, élèves ingénieures, ENSTTIC.
