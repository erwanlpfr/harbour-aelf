Name:       harbour-aelf

Summary:    AELF - Lectures du jour
Version:    1.0.0
Release:    1
License:    GPLv3+
URL:        https://github.com/erwanlpfr/harbour-aelf
Source0:    %{name}-%{version}.tar.bz2

# >> macros
%define __provides_exclude_from ^%{_datadir}/.*$
# << macros

Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Sql)
BuildRequires:  pkgconfig(Qt5Concurrent)
BuildRequires:  desktop-file-utils

%description
Application catholique pour lire les lectures du jour, la messe et la
liturgie des heures depuis le site AELF (Association Épiscopale Liturgique
pour les pays Francophones).

Catholic application for daily readings, mass and liturgy of the hours
from the AELF website (Association Épiscopale Liturgique pour les pays
Francophones). Includes an offline French Bible.


%prep
%setup -q -n %{name}-%{version}

%build

%qmake5 

%make_build

# Don't strip, we'll handle debug symbols
export NO_BRP_STRIP_DEBUG=true


%install
%qmake5_install


desktop-file-install --delete-original         --dir %{buildroot}%{_datadir}/applications                %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png

%changelog
* Sun Feb 02 2025 Erwan - 1.0.0-1
- Initial release
- Catholic application for daily readings, mass and liturgy of the hours
- Integration with AELF website
