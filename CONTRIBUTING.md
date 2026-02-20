# 🇫🇷 Contribuer

Merci de votre intérêt pour AELF ! Ce guide vous aidera à démarrer.

## Environnement de développement

### Prérequis

- [Sailfish SDK](https://docs.sailfishos.org/Tools/Sailfish_SDK/)
- Qt 5.6+ (modules : Core, Qml, Quick, Sql, Concurrent)
- Sailfish Silica >= 0.10.9

### Configuration

```bash
# Configurer la cible de build
sfdk config target=SailfishOS-5.0.0.62-aarch64

# Configurer l'appareil
sfdk config device="Nom de l'appareil"
```

### Compilation et déploiement

```bash
# Compilation complète
sfdk build

# Étapes individuelles
sfdk qmake .
sfdk make
sfdk package

# Déployer sur l'appareil
sfdk deploy --sdk

# Valider le paquet RPM
sfdk check
```

## Style de code

- **C++** : Suivez le fichier `.clang-format` à la racine du projet. Utilisez les conventions Qt standard (camelCase pour les méthodes, préfixe `m_` pour les membres privés).
- **QML** : Indentation de 4 espaces, propriétés groupées par type (id, dimensions, apparence, signaux).
- **Sailfish** : Respectez les [conventions de codage Sailfish OS](https://docs.sailfishos.org/Develop/Apps/Coding_Conventions/).

## Structure du projet

```
src/            # Code source C++ (API, modèles, services, parsers)
qml/            # Interface utilisateur QML
  pages/        # Pages de l'application
  components/   # Composants réutilisables
  cover/        # Page de couverture (écran de verrouillage)
  js/           # Utilitaires JavaScript
  modules/      # Modules OPAL (bibliothèque UI tierce)
assets/         # Base de données Bible (SQLite)
translations/   # Fichiers de traduction Qt (.ts)
rpm/            # Configuration du packaging RPM
icons/          # Icônes de l'application
libs/           # Dépendances OPAL
```

> **Note** : Le dossier `readme/` contient la documentation des modules OPAL, pas celle du projet.

## Traductions

Le français est la langue source. Les traductions sont gérées via le système Qt Linguist.

```bash
# Mettre à jour les fichiers de traduction après modification des sources
lupdate harbour-aelf.pro

# Éditer les traductions
linguist translations/harbour-aelf-en.ts
```

Les fichiers de traduction se trouvent dans `translations/`. Pour ajouter une nouvelle langue :

1. Ajoutez `TRANSLATIONS += translations/harbour-aelf-<code>.ts` dans `harbour-aelf.pro`
2. Exécutez `lupdate harbour-aelf.pro`
3. Traduisez les chaînes avec Qt Linguist
4. Soumettez une pull request

## Soumettre des modifications

1. Forkez le dépôt
2. Créez une branche (`git checkout -b feature/ma-fonctionnalité`)
3. Commitez vos changements avec des messages clairs
4. Poussez vers votre fork (`git push origin feature/ma-fonctionnalité`)
5. Ouvrez une pull request en utilisant le template fourni

## Signaler un bug

Utilisez les templates d'issues fournis sur GitHub. Incluez :
- Votre appareil et version de Sailfish OS
- Les étapes pour reproduire le problème
- Le comportement attendu vs observé

---

# 🇬🇧 Contributing

Thank you for your interest in AELF! This guide will help you get started.

## Development Environment

### Prerequisites

- [Sailfish SDK](https://docs.sailfishos.org/Tools/Sailfish_SDK/)
- Qt 5.6+ (modules: Core, Qml, Quick, Sql, Concurrent)
- Sailfish Silica >= 0.10.9

### Setup

```bash
# Set build target
sfdk config target=SailfishOS-5.0.0.62-aarch64

# Configure device
sfdk config device="Your Device Name"
```

### Build and Deploy

```bash
# Full build
sfdk build

# Individual steps
sfdk qmake .
sfdk make
sfdk package

# Deploy to device
sfdk deploy --sdk

# Validate RPM package
sfdk check
```

## Code Style

- **C++**: Follow the `.clang-format` file at the project root. Use standard Qt conventions (camelCase for methods, `m_` prefix for private members).
- **QML**: 4-space indentation, properties grouped by type (id, dimensions, appearance, signals).
- **Sailfish**: Follow [Sailfish OS coding conventions](https://docs.sailfishos.org/Develop/Apps/Coding_Conventions/).

## Project Structure

```
src/            # C++ source code (API, models, services, parsers)
qml/            # QML user interface
  pages/        # Application pages
  components/   # Reusable components
  cover/        # Cover page (lock screen)
  js/           # JavaScript utilities
  modules/      # OPAL modules (third-party UI library)
assets/         # Bible database (SQLite)
translations/   # Qt translation files (.ts)
rpm/            # RPM packaging configuration
icons/          # Application icons
libs/           # OPAL dependencies
```

> **Note**: The `readme/` directory contains OPAL module documentation, not project documentation.

## Translations

French is the source language. Translations are managed through Qt Linguist.

```bash
# Update translation files after modifying sources
lupdate harbour-aelf.pro

# Edit translations
linguist translations/harbour-aelf-en.ts
```

Translation files are located in `translations/`. To add a new language:

1. Add `TRANSLATIONS += translations/harbour-aelf-<code>.ts` to `harbour-aelf.pro`
2. Run `lupdate harbour-aelf.pro`
3. Translate strings using Qt Linguist
4. Submit a pull request

## Submitting Changes

1. Fork the repository
2. Create a branch (`git checkout -b feature/my-feature`)
3. Commit your changes with clear messages
4. Push to your fork (`git push origin feature/my-feature`)
5. Open a pull request using the provided template

## Reporting Bugs

Use the issue templates provided on GitHub. Include:
- Your device and Sailfish OS version
- Steps to reproduce the issue
- Expected vs actual behavior
