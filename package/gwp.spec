%define name gwp
%define version 0.2.12
%define release 1mdk
%define _unpackaged_files_terminate_build       0
%define _missing_doc_files_terminate_build      0


Summary: GNOME War Pad is a VGA Planets strategy game client for GNOME.
Name: %{name}
Version: %{version}
Release: %{release}
Source0: http://www.lunix.com.ar/~ldipenti/gwp/releases/%{name}-%{version}.tar.gz
License: GPL
Group: Games
BuildRoot: %{_tmppath}/%{name}-buildroot
Prefix: %{_prefix}
requires: gnome2
BuildArch: i586

%description
GNOME War Pad is a VGA Planets client for the
UNIX environment. VGA Planets is a space conquest
strategy, play-by-email, addictive game that can be
played with with 11 players simultaneously.

%prep
%setup -q

%build
./configure --prefix=$RPM_BUILD_ROOT/%{_prefix}
make

%install
make install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_prefix}/share/%{name}
%{_prefix}/share/gnome/help/%{name}
%{_prefix}/share/pixmaps/%{name}/icons
%{_prefix}/share/pixmaps/%{name}/images
%{_prefix}/share/pixmaps/%{name}/planets
%{_prefix}/share/pixmaps/%{name}/ships
%{_prefix}/share/omf/%{name}
%{_prefix}/doc/%{name}

%changelog

# end of file
