// PS5 port frontend: the shelf's and the notifications' text in the PS5's language (vk-285-110).
// See fe_i18n.h. First translations by the port's author; testers' fixes go in /data/PCSX2/lang/<code>.txt.
//
// Copyright (C) 2026 Spyros
// SPDX-License-Identifier: GPL-3.0-or-later

#include "fe_i18n.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace fe
{
namespace
{
constexpr int kCount = static_cast<int>(Str::Count);

const char* const kKeys[kCount] = {
	"hint.play",
	"hint.browse",
	"hint.jump",
	"shelf.no_network",
	"shelf.no_games",
	"covers.downloading",
	"size.gb",
	"size.mb",
	"size.decimal",
	"notify.starting",
	"notify.starting_test",
	"notify.covers_one",
	"notify.covers_many",
	"notify.now_playing",
	"how.native",
	"how.software",
	"notify.no_game",
	"notify.not_started",
	"notify.menu_failed",
	"notify.stopped",
	"hint.settings",
	"hint.move",
	"hint.change",
	"hint.reset",
	"hint.back",
	"sheet.this_game",
	"sheet.all_games",
	"notify.no_bios",
	"notify.gs_failed",
	"sheet.controls",
	"hint.qr_code",
};

const char* const kEnglish[kCount] = {
	"Play",
	"Browse",
	"Jump",
	"Game settings: no network",
	"No games in /data/PS5GBC/games",
	"Downloading covers  %d / %d",
	"%s GB",
	"%s MB",
	".",
	"PS5GBC: starting",
	"PS5GBC (testing build): starting",
	"PS5GBC: downloading %d cover",
	"PS5GBC: downloading %d covers",
	"Now playing: %s\n%s · have fun!",
	"native %s",
	"software renderer",
	"PS5GBC: no game to start. Put your .gb/.gbc or .zip files in /data/PS5GBC/games/ or on a USB drive, then start PS5GBC again.",
	"PS5GBC: the game didn't start.\n%s",
	"PS5GBC: couldn't open the menu, back to the game",
	"PS5GBC: the game stopped",
	"Settings",
	"Move",
	"Change",
	"Reset",
	"Back",
	"This game",
	"All games",
	"PS5GBC: no PS2 BIOS found. Copy your BIOS file (4 MB, e.g. SCPH-70012.bin) to %s and start the game again.",
	"PS5GBC: the game's graphics didn't start. Start it again; if it happens again, reinstall PS5GBC with its installer.",
	"Controls",
	"QR code",
};

const char* const kSpanish[kCount] = {
	"Jugar",
	"Explorar",
	"Saltar",
	"Ajustes del juego: sin red",
	"No hay juegos en /data/PS5GBC/games",
	"Descargando carátulas  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: iniciando",
	"PS5GBC (versión de prueba): iniciando",
	"PS5GBC: descargando %d carátula",
	"PS5GBC: descargando %d carátulas",
	"Jugando: %s\n%s · ¡que lo disfrutes!",
	"resolución nativa, %s",
	"renderizado por software",
	"PS5GBC: no hay ningún juego para iniciar. Pon tus archivos .sfc o .smc en /data/PS5GBC/games/ o en una unidad USB y vuelve a abrir PS5GBC.",
	"PS5GBC: el juego no se ha iniciado.\n%s",
	"PS5GBC: no se ha podido abrir el menú; vuelves al juego",
	"PS5GBC: el juego se ha detenido",
	"Ajustes",
	"Mover",
	"Cambiar",
	"Restablecer",
	"Atrás",
	"Este juego",
	"Todos los juegos",
	"PS5GBC: no se ha encontrado ninguna BIOS de PS2. Copia tu archivo de BIOS (4 MB, p. ej. SCPH-70012.bin) en %s y vuelve a iniciar el juego.",
	"PS5GBC: los gráficos del juego no se han iniciado. Vuelve a iniciarlo; si vuelve a pasar, reinstala PS5GBC con su instalador.",
	"Controles",
	"Código QR",
};

const char* const kSpanishLatAm[kCount] = {
	"Jugar",
	"Explorar",
	"Saltar",
	"Configuración del juego: sin red",
	"No hay juegos en /data/PS5GBC/games",
	"Descargando portadas  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: iniciando",
	"PS5GBC (versión de prueba): iniciando",
	"PS5GBC: descargando %d portada",
	"PS5GBC: descargando %d portadas",
	"Jugando: %s\n%s · ¡que lo disfrutes!",
	"resolución nativa, %s",
	"renderizado por software",
	"PS5GBC: no hay ningún juego para iniciar. Coloca tus archivos .sfc o .smc en /data/PS5GBC/games/ o en una unidad USB y vuelve a abrir PS5GBC.",
	"PS5GBC: el juego no se inició.\n%s",
	"PS5GBC: no se pudo abrir el menú; vuelves al juego",
	"PS5GBC: el juego se detuvo",
	"Ajustes",
	"Mover",
	"Cambiar",
	"Restablecer",
	"Atrás",
	"Este juego",
	"Todos los juegos",
	"PS5GBC: no se encontró ninguna BIOS de PS2. Copia tu archivo de BIOS (4 MB, p. ej. SCPH-70012.bin) en %s y vuelve a iniciar el juego.",
	"PS5GBC: los gráficos del juego no se iniciaron. Vuelve a iniciarlo; si vuelve a pasar, reinstala PS5GBC con su instalador.",
	"Controles",
	"Código QR",
};

const char* const kFrench[kCount] = {
	"Jouer",
	"Parcourir",
	"Sauter",
	"Réglages du jeu : pas de réseau",
	"Aucun jeu dans /data/PS5GBC/games",
	"Téléchargement des jaquettes  %d / %d",
	"%s Go",
	"%s Mo",
	",",
	"PS5GBC : démarrage",
	"PS5GBC (version de test) : démarrage",
	"PS5GBC : téléchargement de %d jaquette",
	"PS5GBC : téléchargement de %d jaquettes",
	"En jeu : %s\n%s · bon jeu !",
	"résolution native, %s",
	"rendu logiciel",
	"PS5GBC : aucun jeu à lancer. Mets tes fichiers .sfc ou .smc dans /data/PS5GBC/games/ ou sur une clé USB, puis relance PS5GBC.",
	"PS5GBC : le jeu n'a pas démarré.\n%s",
	"PS5GBC : impossible d'ouvrir le menu, retour au jeu",
	"PS5GBC : le jeu s'est arrêté",
	"Réglages",
	"Déplacer",
	"Modifier",
	"Réinitialiser",
	"Retour",
	"Ce jeu",
	"Tous les jeux",
	"PS5GBC : aucun BIOS PS2 trouvé. Copie ton fichier BIOS (4 Mo, par ex. SCPH-70012.bin) dans %s, puis relance le jeu.",
	"PS5GBC : les graphismes du jeu n'ont pas démarré. Relance-le ; si ça recommence, réinstalle PS5GBC avec son installateur.",
	"Commandes",
	"Code QR",
};

const char* const kGerman[kCount] = {
	"Spielen",
	"Blättern",
	"Springen",
	"Spieleinstellungen: kein Netzwerk",
	"Keine Spiele in /data/PS5GBC/games",
	"Cover werden geladen  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: wird gestartet",
	"PS5GBC (Testversion): wird gestartet",
	"PS5GBC: %d Cover wird geladen",
	"PS5GBC: %d Cover werden geladen",
	"Jetzt läuft: %s\n%s · viel Spaß!",
	"native Auflösung, %s",
	"Software-Renderer",
	"PS5GBC: Kein Spiel zum Starten. Lege deine .sfc- oder .smc-Dateien in /data/PS5GBC/games/ oder auf ein USB-Laufwerk und starte PS5GBC dann neu.",
	"PS5GBC: Das Spiel ist nicht gestartet.\n%s",
	"PS5GBC: Das Menü konnte nicht geöffnet werden, zurück zum Spiel",
	"PS5GBC: Das Spiel wurde beendet",
	"Einstellungen",
	"Bewegen",
	"Ändern",
	"Zurücksetzen",
	"Zurück",
	"Dieses Spiel",
	"Alle Spiele",
	"PS5GBC: Kein PS2-BIOS gefunden. Kopiere deine BIOS-Datei (4 MB, z. B. SCPH-70012.bin) nach %s und starte das Spiel erneut.",
	"PS5GBC: Die Grafik des Spiels ist nicht gestartet. Starte es erneut; passiert es wieder, installiere PS5GBC mit seinem Installer neu.",
	"Steuerung",
	"QR-Code",
};

const char* const kItalian[kCount] = {
	"Gioca",
	"Sfoglia",
	"Salta",
	"Impostazioni di gioco: nessuna rete",
	"Nessun gioco in /data/PS5GBC/games",
	"Download copertine  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: avvio",
	"PS5GBC (versione di prova): avvio",
	"PS5GBC: download di %d copertina",
	"PS5GBC: download di %d copertine",
	"In gioco: %s\n%s · buon divertimento!",
	"risoluzione nativa, %s",
	"rendering software",
	"PS5GBC: nessun gioco da avviare. Metti i tuoi file .sfc o .smc in /data/PS5GBC/games/ o su un'unità USB, poi riapri PS5GBC.",
	"PS5GBC: il gioco non si è avviato.\n%s",
	"PS5GBC: impossibile aprire il menu, si torna al gioco",
	"PS5GBC: il gioco si è fermato",
	"Impostazioni",
	"Sposta",
	"Cambia",
	"Ripristina",
	"Indietro",
	"Questo gioco",
	"Tutti i giochi",
	"PS5GBC: nessun BIOS PS2 trovato. Copia il tuo file BIOS (4 MB, ad es. SCPH-70012.bin) in %s e riavvia il gioco.",
	"PS5GBC: la grafica del gioco non si è avviata. Riavvialo; se succede di nuovo, reinstalla PS5GBC con il suo programma di installazione.",
	"Comandi",
	"Codice QR",
};

const char* const kDutch[kCount] = {
	"Spelen",
	"Bladeren",
	"Springen",
	"Spelinstellingen: geen netwerk",
	"Geen games in /data/PS5GBC/games",
	"Covers downloaden  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: wordt gestart",
	"PS5GBC (testversie): wordt gestart",
	"PS5GBC: %d cover downloaden",
	"PS5GBC: %d covers downloaden",
	"Nu speel je: %s\n%s · veel plezier!",
	"native resolutie, %s",
	"softwarerenderer",
	"PS5GBC: geen game om te starten. Zet je .sfc- of .smc-bestanden in /data/PS5GBC/games/ of op een USB-stick en start PS5GBC opnieuw.",
	"PS5GBC: de game is niet gestart.\n%s",
	"PS5GBC: het menu kon niet worden geopend, terug naar de game",
	"PS5GBC: de game is gestopt",
	"Instellingen",
	"Verplaatsen",
	"Wijzigen",
	"Herstellen",
	"Terug",
	"Dit spel",
	"Alle spellen",
	"PS5GBC: geen PS2-BIOS gevonden. Kopieer je BIOS-bestand (4 MB, bijv. SCPH-70012.bin) naar %s en start de game opnieuw.",
	"PS5GBC: de graphics van de game zijn niet gestart. Start de game opnieuw; gebeurt het weer, installeer PS5GBC dan opnieuw met het installatieprogramma.",
	"Besturing",
	"QR-code",
};

const char* const kPortuguese[kCount] = {
	"Jogar",
	"Navegar",
	"Saltar",
	"Definições do jogo: sem rede",
	"Nenhum jogo em /data/PS5GBC/games",
	"A transferir capas  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: a iniciar",
	"PS5GBC (versão de teste): a iniciar",
	"PS5GBC: a transferir %d capa",
	"PS5GBC: a transferir %d capas",
	"A jogar: %s\n%s · diverte-te!",
	"resolução nativa, %s",
	"renderização por software",
	"PS5GBC: nenhum jogo para iniciar. Coloca os teus ficheiros .sfc ou .smc em /data/PS5GBC/games/ ou numa pen USB e volta a abrir o PS5GBC.",
	"PS5GBC: o jogo não arrancou.\n%s",
	"PS5GBC: não foi possível abrir o menu, de volta ao jogo",
	"PS5GBC: o jogo parou",
	"Definições",
	"Mover",
	"Alterar",
	"Repor",
	"Voltar",
	"Este jogo",
	"Todos os jogos",
	"PS5GBC: nenhuma BIOS da PS2 encontrada. Copia o teu ficheiro de BIOS (4 MB, por ex. SCPH-70012.bin) para %s e volta a iniciar o jogo.",
	"PS5GBC: os gráficos do jogo não arrancaram. Volta a iniciá-lo; se acontecer de novo, reinstala o PS5GBC com o instalador.",
	"Controlos",
	"Código QR",
};

const char* const kPortugueseBrazil[kCount] = {
	"Jogar",
	"Navegar",
	"Pular",
	"Configurações do jogo: sem rede",
	"Nenhum jogo em /data/PS5GBC/games",
	"Baixando capas  %d / %d",
	"%s GB",
	"%s MB",
	",",
	"PS5GBC: iniciando",
	"PS5GBC (versão de teste): iniciando",
	"PS5GBC: baixando %d capa",
	"PS5GBC: baixando %d capas",
	"Jogando: %s\n%s · divirta-se!",
	"resolução nativa, %s",
	"renderização por software",
	"PS5GBC: nenhum jogo para iniciar. Coloque seus arquivos .sfc ou .smc em /data/PS5GBC/games/ ou em um pendrive e abra o PS5GBC de novo.",
	"PS5GBC: o jogo não iniciou.\n%s",
	"PS5GBC: não foi possível abrir o menu, voltando ao jogo",
	"PS5GBC: o jogo parou",
	"Configurações",
	"Mover",
	"Alterar",
	"Redefinir",
	"Voltar",
	"Este jogo",
	"Todos os jogos",
	"PS5GBC: nenhuma BIOS de PS2 encontrada. Copie seu arquivo de BIOS (4 MB, ex.: SCPH-70012.bin) para %s e inicie o jogo de novo.",
	"PS5GBC: os gráficos do jogo não iniciaram. Inicie de novo; se acontecer outra vez, reinstale o PS5GBC com o instalador.",
	"Controles",
	"QR code",
};

// The region names fe_games.cpp takes from a file name's first group (kRegions there), in its order.
constexpr int kRegionCount = 19;
const char* const kRegionsEnglish[kRegionCount] = {"USA", "Europe", "Japan", "Korea", "Asia", "World", "Australia",
	"France", "Germany", "Italy", "Spain", "UK", "Canada", "Brazil", "Russia", "China", "Taiwan", "Netherlands", "Sweden"};
const char* const kRegionsSpanish[kRegionCount] = {"EE. UU.", "Europa", "Japón", "Corea", "Asia", "Mundo", "Australia",
	"Francia", "Alemania", "Italia", "España", "Reino Unido", "Canadá", "Brasil", "Rusia", "China", "Taiwán",
	"Países Bajos", "Suecia"};
const char* const kRegionsFrench[kRegionCount] = {"États-Unis", "Europe", "Japon", "Corée", "Asie", "Monde",
	"Australie", "France", "Allemagne", "Italie", "Espagne", "Royaume-Uni", "Canada", "Brésil", "Russie", "Chine",
	"Taïwan", "Pays-Bas", "Suède"};
const char* const kRegionsGerman[kRegionCount] = {"USA", "Europa", "Japan", "Korea", "Asien", "Welt", "Australien",
	"Frankreich", "Deutschland", "Italien", "Spanien", "Großbritannien", "Kanada", "Brasilien", "Russland", "China",
	"Taiwan", "Niederlande", "Schweden"};
const char* const kRegionsItalian[kRegionCount] = {"USA", "Europa", "Giappone", "Corea", "Asia", "Mondo", "Australia",
	"Francia", "Germania", "Italia", "Spagna", "Regno Unito", "Canada", "Brasile", "Russia", "Cina", "Taiwan",
	"Paesi Bassi", "Svezia"};
const char* const kRegionsDutch[kRegionCount] = {"VS", "Europa", "Japan", "Korea", "Azië", "Wereld", "Australië",
	"Frankrijk", "Duitsland", "Italië", "Spanje", "VK", "Canada", "Brazilië", "Rusland", "China", "Taiwan",
	"Nederland", "Zweden"};
const char* const kRegionsPortuguese[kRegionCount] = {"EUA", "Europa", "Japão", "Coreia", "Ásia", "Mundo",
	"Austrália", "França", "Alemanha", "Itália", "Espanha", "Reino Unido", "Canadá", "Brasil", "Rússia", "China",
	"Taiwan", "Países Baixos", "Suécia"};
const char* const kRegionsPortugueseBrazil[kRegionCount] = {"EUA", "Europa", "Japão", "Coreia", "Ásia", "Mundo",
	"Austrália", "França", "Alemanha", "Itália", "Espanha", "Reino Unido", "Canadá", "Brasil", "Rússia", "China",
	"Taiwan", "Holanda", "Suécia"};

struct Language
{
	const char* code;
	const char* const* text;
	const char* const* regions;
};

const Language kLanguages[] = {
	{"en", kEnglish, kRegionsEnglish},
	{"fr", kFrench, kRegionsFrench},
	{"es", kSpanish, kRegionsSpanish},
	{"es-419", kSpanishLatAm, kRegionsSpanish},
	{"de", kGerman, kRegionsGerman},
	{"it", kItalian, kRegionsItalian},
	{"nl", kDutch, kRegionsDutch},
	{"pt", kPortuguese, kRegionsPortuguese},
	{"pt-BR", kPortugueseBrazil, kRegionsPortugueseBrazil},
};

const Language* s_lang = &kLanguages[0];
std::vector<std::string> s_text_over(kCount);
std::vector<std::string> s_region_over(kRegionCount);

// The PS5's language ids (as the PS4's: 0 Japanese, 1 English (US), 2 French, 3 Spanish, 4 German, 5 Italian,
// 6 Dutch, 7 Portuguese, 17 Portuguese (Brazil), 18 English (UK), 20 Spanish (Latin America), 22 French
// (Canada); the others have no table here).
const Language* LanguageFor(int ps5)
{
	switch (ps5)
	{
		case 2:
		case 22:
			return &kLanguages[1];
		case 3:
			return &kLanguages[2];
		case 20:
			return &kLanguages[3];
		case 4:
			return &kLanguages[4];
		case 5:
			return &kLanguages[5];
		case 6:
			return &kLanguages[6];
		case 7:
			return &kLanguages[7];
		case 17:
			return &kLanguages[8];
		default:
			return &kLanguages[0];
	}
}

std::string Trim(const std::string& s)
{
	size_t a = 0, b = s.size();
	while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\r' || s[a] == '\n'))
		a++;
	while (b > a && (s[b - 1] == ' ' || s[b - 1] == '\t' || s[b - 1] == '\r' || s[b - 1] == '\n'))
		b--;
	return s.substr(a, b - a);
}

// "\n" in a value is a line break.
std::string Unescape(const std::string& s)
{
	std::string out;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s[i] == '\\' && i + 1 < s.size() && s[i + 1] == 'n')
		{
			out += '\n';
			i++;
		}
		else
			out += s[i];
	}
	return out;
}

// The conversions of a printf format, in order ("%d / %d" -> "dd"); an unfinished one gives "?".
std::string Conversions(const char* f)
{
	std::string out;
	for (const char* p = f; *p; p++)
	{
		if (*p != '%')
			continue;
		p++;
		if (*p == '%')
			continue;
		while (*p && std::strchr("-+ #0123456789.lhzjt", *p))
			p++;
		if (!*p)
		{
			out += '?';
			break;
		}
		out += *p;
	}
	return out;
}

void LoadOverrides(const std::string& path)
{
	FILE* f = std::fopen(path.c_str(), "rb");
	if (!f)
		return;
	int used = 0, refused = 0;
	char line[1024];
	while (std::fgets(line, sizeof(line), f))
	{
		std::string l = Trim(line);
		if (l.size() >= 3 && static_cast<unsigned char>(l[0]) == 0xEF && static_cast<unsigned char>(l[1]) == 0xBB &&
			static_cast<unsigned char>(l[2]) == 0xBF)
			l = Trim(l.substr(3)); // a byte-order mark from Notepad
		if (l.empty() || l[0] == '#' || l[0] == ';')
			continue;
		const size_t eq = l.find('=');
		if (eq == std::string::npos)
			continue;
		const std::string key = Trim(l.substr(0, eq));
		const std::string value = Unescape(Trim(l.substr(eq + 1)));
		bool known = false;
		for (int i = 0; i < kCount; i++)
			if (key == kKeys[i])
			{
				known = true;
				if (value.empty() || !SameFormat(kEnglish[i], value.c_str()))
				{
					std::printf("[i18n] %s: %s refused (it has to keep the English text's %%d and %%s, in order)\n", path.c_str(),
						key.c_str());
					refused++;
				}
				else
				{
					s_text_over[i] = value;
					used++;
				}
			}
		if (key.compare(0, 7, "region.") == 0)
			for (int i = 0; i < kRegionCount; i++)
				if (key.compare(7, std::string::npos, kRegionsEnglish[i]) == 0 && !value.empty() && value.find('%') == std::string::npos)
				{
					known = true;
					s_region_over[i] = value;
					used++;
				}
		if (!known)
		{
			std::printf("[i18n] %s: unknown key %s\n", path.c_str(), key.c_str());
			refused++;
		}
	}
	std::fclose(f);
	std::printf("[i18n] %s: %d entries used, %d refused\n", path.c_str(), used, refused);
}
} // namespace

void SetLanguage(int ps5_language, const std::string& lang_dir)
{
	s_lang = LanguageFor(1);
	for (std::string& s : s_text_over)
		s.clear();
	for (std::string& s : s_region_over)
		s.clear();
	std::printf("[i18n] PS5 language %d: text in %s\n", ps5_language, s_lang->code);
	if (!lang_dir.empty())
		LoadOverrides(lang_dir + "/" + s_lang->code + ".txt");
	std::fflush(stdout);
}

const char* Tr(Str id)
{
	const int i = static_cast<int>(id);
	if (i < 0 || i >= kCount)
		return "";
	if (!s_text_over[static_cast<size_t>(i)].empty())
		return s_text_over[static_cast<size_t>(i)].c_str();
	const char* t = s_lang->text[i];
	return t ? t : kEnglish[i];
}

const char* LanguageCode()
{
	return s_lang->code;
}

const char* Key(Str id)
{
	const int i = static_cast<int>(id);
	return i >= 0 && i < kCount ? kKeys[i] : "";
}

std::string Region(const std::string& region)
{
	std::string out;
	size_t pos = 0;
	while (pos <= region.size())
	{
		size_t comma = region.find(", ", pos);
		if (comma == std::string::npos)
			comma = region.size();
		const std::string token = region.substr(pos, comma - pos);
		std::string shown = token;
		for (int i = 0; i < kRegionCount; i++)
			if (token == kRegionsEnglish[i])
				shown = !s_region_over[static_cast<size_t>(i)].empty() ? s_region_over[static_cast<size_t>(i)] : s_lang->regions[i];
		if (!out.empty())
			out += ", ";
		out += shown;
		pos = comma + 2;
	}
	return out;
}

std::string Size(uint64_t bytes)
{
	char num[32];
	const double gb = static_cast<double>(bytes) / 1e9;
	const bool big = gb >= 1.0;
	if (big)
		std::snprintf(num, sizeof(num), "%.1f", gb);
	else
		std::snprintf(num, sizeof(num), "%.0f", static_cast<double>(bytes) / 1e6);
	std::string n = num;
	const std::string dec = Tr(Str::Decimal);
	const size_t dot = n.find('.');
	if (dot != std::string::npos)
		n.replace(dot, 1, dec);
	char out[64];
	std::snprintf(out, sizeof(out), Tr(big ? Str::SizeGB : Str::SizeMB), n.c_str());
	return out;
}

int Ps2LanguageFor(int ps5_language)
{
	switch (ps5_language)
	{
		case 0:
			return 0; // Japanese
		case 1:
		case 18:
			return 1; // English (US, UK)
		case 2:
		case 22:
			return 2; // French (France, Canada)
		case 3:
		case 20:
			return 3; // Spanish (Spain, Latin America)
		case 4:
			return 4; // German
		case 5:
			return 5; // Italian
		case 6:
			return 6; // Dutch
		case 7:
		case 17:
			return 7; // Portuguese (Portugal, Brazil)
		default:
			return 1; // no such language on the PS2: English
	}
}

const char* Ps2LanguageName(int ps2_language)
{
	static const char* const names[] = {"Japanese", "English", "French", "Spanish", "German", "Italian", "Dutch", "Portuguese"};
	return ps2_language >= 0 && ps2_language < 8 ? names[ps2_language] : "?";
}

bool SameFormat(const char* a, const char* b)
{
	return Conversions(a) == Conversions(b);
}
} // namespace fe
