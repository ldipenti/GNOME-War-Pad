%define name gwp
%define version 0.3.0
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
#requires: libgnome2 libglade2.0
AutoReqProv: yes
BuildArch: i586

%description
GNOME War Pad is a VGA Planets client for the
UNIX environment. VGA Planets is a space conquest
strategy, play-by-email, addictive game that can be
played with with 11 players simultaneously.

%prep
%setup -q

%build
%configure
%make

%install
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{_prefix}/bin
%{_prefix}/share/%{name}
%{_prefix}/share/gnome/help/%{name}
%{_prefix}/share/gnome/apps/Games
%{_prefix}/share/pixmaps
%{_prefix}/share/locale
%{_prefix}/share/omf/%{name}
%{_prefix}/doc/%{name}

%changelog

# end of file
