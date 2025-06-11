/* clang-format off */
/*
 * @file general.h
 * @date 2025-06-04
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
#ifndef GENERAL_H
#define GENERAL_H
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <CommCtrl.h>
#include <cstdint>
#include <string>
#include "helper/convert.h"
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(linker, "\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "User32.Lib")
namespace YanLib::ui::components {
#ifndef COMMONSTYLE
#define COMMONSTYLE
    enum class CommonStyle : uint32_t {
        Top = CCS_TOP,
        NoMoveY = CCS_NOMOVEY,
        Bottom = CCS_BOTTOM,
        NoResize = CCS_NORESIZE,
        NoParentAlign = CCS_NOPARENTALIGN,
        Adjustable = CCS_ADJUSTABLE,
        NoDivider = CCS_NODIVIDER,
        Vert = CCS_VERT,
        Left = CCS_LEFT,
        Right = CCS_RIGHT,
        NoMoveX = CCS_NOMOVEX,
    };
    inline CommonStyle operator|(CommonStyle a, CommonStyle b) {
        return static_cast<CommonStyle>(static_cast<uint32_t>(a) |
                                        static_cast<uint32_t>(b));
    }
#endif
#ifndef INITCOMMCONTROLSFLAG
#define INITCOMMCONTROLSFLAG
    enum class InitCommControlsFlag : uint32_t {
        ListView = ICC_LISTVIEW_CLASSES, // listview, header
        TreeView = ICC_TREEVIEW_CLASSES, // treeview, tooltips
        Bar = ICC_BAR_CLASSES,         // toolbar, statusbar, trackbar, tooltips
        Tab = ICC_TAB_CLASSES,         // tab, tooltips
        UpDown = ICC_UPDOWN_CLASS,     // updown
        Progress = ICC_PROGRESS_CLASS, // progress
        HotKey = ICC_HOTKEY_CLASS,     // hotkey
        Animate = ICC_ANIMATE_CLASS,   // animate
        Win95 = ICC_WIN95_CLASSES,
        Date = ICC_DATE_CLASSES,     // month picker, date picker, time picker,
                                     // updown
        UserEx = ICC_USEREX_CLASSES, // comboex
        Cool = ICC_COOL_CLASSES,     // rebar (coolbar) control
        Internet = ICC_INTERNET_CLASSES,
        PageScroller = ICC_PAGESCROLLER_CLASS, // page scroller
        NativeFntCtl = ICC_NATIVEFNTCTL_CLASS, // native font control
        Standard = ICC_STANDARD_CLASSES,
        Link = ICC_LINK_CLASS,
    };
    inline InitCommControlsFlag operator|(InitCommControlsFlag a,
                                          InitCommControlsFlag b) {
        return static_cast<InitCommControlsFlag>(static_cast<uint32_t>(a) |
                                                 static_cast<uint32_t>(b));
    }
#endif
#ifndef GENERALLANGID
#define GENERALLANGID
    enum class GeneralLangID : uint16_t {
        Neutral = LANG_NEUTRAL,
        Invariant = LANG_INVARIANT,
        Afrikaans = LANG_AFRIKAANS,
        Albanian = LANG_ALBANIAN,
        Alsatian = LANG_ALSATIAN,
        Amharic = LANG_AMHARIC,
        Arabic = LANG_ARABIC,
        Armenian = LANG_ARMENIAN,
        Assamese = LANG_ASSAMESE,
        Azeri = LANG_AZERI,
        Azerbaijani = LANG_AZERBAIJANI,
        Bangla = LANG_BANGLA,
        Bashkir = LANG_BASHKIR,
        Basque = LANG_BASQUE,
        Belarusian = LANG_BELARUSIAN,
        Bengali = LANG_BENGALI,
        Breton = LANG_BRETON,
        Bosnian = LANG_BOSNIAN,
        BosnianNeutral = LANG_BOSNIAN_NEUTRAL,
        Bulgarian = LANG_BULGARIAN,
        Catalan = LANG_CATALAN,
        CentralKurdish = LANG_CENTRAL_KURDISH,
        Cherokee = LANG_CHEROKEE,
        Chinese = LANG_CHINESE,
        ChineseSimplified = LANG_CHINESE_SIMPLIFIED,
        ChineseTraditional = LANG_CHINESE_TRADITIONAL,
        Corsican = LANG_CORSICAN,
        Croatian = LANG_CROATIAN,
        Czech = LANG_CZECH,
        Danish = LANG_DANISH,
        Dari = LANG_DARI,
        Divehi = LANG_DIVEHI,
        Dutch = LANG_DUTCH,
        English = LANG_ENGLISH,
        Estonian = LANG_ESTONIAN,
        Faeroese = LANG_FAEROESE,
        Farsi = LANG_FARSI,
        Filipino = LANG_FILIPINO,
        Finnish = LANG_FINNISH,
        French = LANG_FRENCH,
        Frisian = LANG_FRISIAN,
        Fulah = LANG_FULAH,
        Galician = LANG_GALICIAN,
        Georgian = LANG_GEORGIAN,
        German = LANG_GERMAN,
        Greek = LANG_GREEK,
        Greenlandic = LANG_GREENLANDIC,
        Gujarati = LANG_GUJARATI,
        Hausa = LANG_HAUSA,
        Hawaiian = LANG_HAWAIIAN,
        Hebrew = LANG_HEBREW,
        Hindi = LANG_HINDI,
        Hungarian = LANG_HUNGARIAN,
        Icelandic = LANG_ICELANDIC,
        Igbo = LANG_IGBO,
        Indonesian = LANG_INDONESIAN,
        Inuktitut = LANG_INUKTITUT,
        Irish = LANG_IRISH,
        Italian = LANG_ITALIAN,
        Japanese = LANG_JAPANESE,
        Kannada = LANG_KANNADA,
        Kashmiri = LANG_KASHMIRI,
        Kazak = LANG_KAZAK,
        Khmer = LANG_KHMER,
        Kiche = LANG_KICHE,
        Kinyarwanda = LANG_KINYARWANDA,
        Konkani = LANG_KONKANI,
        Korean = LANG_KOREAN,
        Kyrgyz = LANG_KYRGYZ,
        Lao = LANG_LAO,
        Latvian = LANG_LATVIAN,
        Lithuanian = LANG_LITHUANIAN,
        LowerSorbian = LANG_LOWER_SORBIAN,
        Luxembourgish = LANG_LUXEMBOURGISH,
        Macedonian = LANG_MACEDONIAN,
        Malay = LANG_MALAY,
        Malayalam = LANG_MALAYALAM,
        Maltese = LANG_MALTESE,
        Manipuri = LANG_MANIPURI,
        Maori = LANG_MAORI,
        Mapudungun = LANG_MAPUDUNGUN,
        Marathi = LANG_MARATHI,
        Mohawk = LANG_MOHAWK,
        Mongolian = LANG_MONGOLIAN,
        Nepali = LANG_NEPALI,
        Norwegian = LANG_NORWEGIAN,
        Occitan = LANG_OCCITAN,
        Odia = LANG_ODIA,
        Oriya = LANG_ORIYA,
        Pashto = LANG_PASHTO,
        Persian = LANG_PERSIAN,
        Polish = LANG_POLISH,
        Portuguese = LANG_PORTUGUESE,
        Pular = LANG_PULAR,
        Punjabi = LANG_PUNJABI,
        Quechua = LANG_QUECHUA,
        Romanian = LANG_ROMANIAN,
        Romansh = LANG_ROMANSH,
        Russian = LANG_RUSSIAN,
        Sakha = LANG_SAKHA,
        Sami = LANG_SAMI,
        Sanskrit = LANG_SANSKRIT,
        ScottishGaelic = LANG_SCOTTISH_GAELIC,
        Serbian = LANG_SERBIAN,
        SerbianNeutral = LANG_SERBIAN_NEUTRAL,
        Sindhi = LANG_SINDHI,
        Sinhalese = LANG_SINHALESE,
        Slovak = LANG_SLOVAK,
        Slovenian = LANG_SLOVENIAN,
        Sotho = LANG_SOTHO,
        Spanish = LANG_SPANISH,
        Swahili = LANG_SWAHILI,
        Swedish = LANG_SWEDISH,
        Syriac = LANG_SYRIAC,
        Tajik = LANG_TAJIK,
        Tamazight = LANG_TAMAZIGHT,
        Tamil = LANG_TAMIL,
        Tatar = LANG_TATAR,
        Telugu = LANG_TELUGU,
        Thai = LANG_THAI,
        Tibetan = LANG_TIBETAN,
        Tigrigna = LANG_TIGRIGNA,
        Tigrinya = LANG_TIGRINYA,
        Tswana = LANG_TSWANA,
        Turkish = LANG_TURKISH,
        Turkmen = LANG_TURKMEN,
        Uighur = LANG_UIGHUR,
        Ukrainian = LANG_UKRAINIAN,
        UpperSorbian = LANG_UPPER_SORBIAN,
        Urdu = LANG_URDU,
        Uzbek = LANG_UZBEK,
        Valencian = LANG_VALENCIAN,
        Vietnamese = LANG_VIETNAMESE,
        Welsh = LANG_WELSH,
        Wolof = LANG_WOLOF,
        Xhosa = LANG_XHOSA,
        Yakut = LANG_YAKUT,
        Yi = LANG_YI,
        Yoruba = LANG_YORUBA,
        Zulu = LANG_ZULU
    };
#endif
#ifndef GENERALSUBLANGID
#define GENERALSUBLANGID
    enum class GeneralSubLangId : uint16_t {
        Neutral = SUBLANG_NEUTRAL,
        Default = SUBLANG_DEFAULT,
        SysDefault = SUBLANG_SYS_DEFAULT,
        CustomDefault = SUBLANG_CUSTOM_DEFAULT,
        CustomUnspecified = SUBLANG_CUSTOM_UNSPECIFIED,
        UiCustomDefault = SUBLANG_UI_CUSTOM_DEFAULT,
        AfrikaansSouthAfrica = SUBLANG_AFRIKAANS_SOUTH_AFRICA,
        AlbanianAlbania = SUBLANG_ALBANIAN_ALBANIA,
        AlsatianFrance = SUBLANG_ALSATIAN_FRANCE,
        AmharicEthiopia = SUBLANG_AMHARIC_ETHIOPIA,
        ArabicSaudiArabia = SUBLANG_ARABIC_SAUDI_ARABIA,
        ArabicIraq = SUBLANG_ARABIC_IRAQ,
        ArabicEgypt = SUBLANG_ARABIC_EGYPT,
        ArabicLibya = SUBLANG_ARABIC_LIBYA,
        ArabicAlgeria = SUBLANG_ARABIC_ALGERIA,
        ArabicMorocco = SUBLANG_ARABIC_MOROCCO,
        ArabicTunisia = SUBLANG_ARABIC_TUNISIA,
        ArabicOman = SUBLANG_ARABIC_OMAN,
        ArabicYemen = SUBLANG_ARABIC_YEMEN,
        ArabicSyria = SUBLANG_ARABIC_SYRIA,
        ArabicJordan = SUBLANG_ARABIC_JORDAN,
        ArabicLebanon = SUBLANG_ARABIC_LEBANON,
        ArabicKuwait = SUBLANG_ARABIC_KUWAIT,
        ArabicUae = SUBLANG_ARABIC_UAE,
        ArabicBahrain = SUBLANG_ARABIC_BAHRAIN,
        ArabicQatar = SUBLANG_ARABIC_QATAR,
        ArmenianArmenia = SUBLANG_ARMENIAN_ARMENIA,
        AssameseIndia = SUBLANG_ASSAMESE_INDIA,
        AzeriLatin = SUBLANG_AZERI_LATIN,
        AzeriCyrillic = SUBLANG_AZERI_CYRILLIC,
        AzerbaijaniAzerbaijanLatin = SUBLANG_AZERBAIJANI_AZERBAIJAN_LATIN,
        AzerbaijaniAzerbaijanCyrillic = SUBLANG_AZERBAIJANI_AZERBAIJAN_CYRILLIC,
        BanglaIndia = SUBLANG_BANGLA_INDIA,
        BanglaBangladesh = SUBLANG_BANGLA_BANGLADESH,
        BashkirRussia = SUBLANG_BASHKIR_RUSSIA,
        BasqueBasque = SUBLANG_BASQUE_BASQUE,
        BelarusianBelarus = SUBLANG_BELARUSIAN_BELARUS,
        BengaliIndia = SUBLANG_BENGALI_INDIA,
        BengaliBangladesh = SUBLANG_BENGALI_BANGLADESH,
        BosnianBosniaHerzegovinaLatin =
                SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN,
        BosnianBosniaHerzegovinaCyrillic =
                SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC,
        BretonFrance = SUBLANG_BRETON_FRANCE,
        BulgarianBulgaria = SUBLANG_BULGARIAN_BULGARIA,
        CatalanCatalan = SUBLANG_CATALAN_CATALAN,
        CentralKurdishIraq = SUBLANG_CENTRAL_KURDISH_IRAQ,
        CherokeeCherokee = SUBLANG_CHEROKEE_CHEROKEE,
        ChineseTraditional = SUBLANG_CHINESE_TRADITIONAL,
        ChineseSimplified = SUBLANG_CHINESE_SIMPLIFIED,
        ChineseHongKong = SUBLANG_CHINESE_HONGKONG,
        ChineseSingapore = SUBLANG_CHINESE_SINGAPORE,
        ChineseMacau = SUBLANG_CHINESE_MACAU,
        CorsicanFrance = SUBLANG_CORSICAN_FRANCE,
        CzechCzechRepublic = SUBLANG_CZECH_CZECH_REPUBLIC,
        CroatianCroatia = SUBLANG_CROATIAN_CROATIA,
        CroatianBosniaHerzegovinaLatin =
                SUBLANG_CROATIAN_BOSNIA_HERZEGOVINA_LATIN,
        DanishDenmark = SUBLANG_DANISH_DENMARK,
        DariAfghanistan = SUBLANG_DARI_AFGHANISTAN,
        DivehiMaldives = SUBLANG_DIVEHI_MALDIVES,
        Dutch = SUBLANG_DUTCH,
        DutchBelgian = SUBLANG_DUTCH_BELGIAN,
        EnglishUs = SUBLANG_ENGLISH_US,
        EnglishUk = SUBLANG_ENGLISH_UK,
        EnglishAus = SUBLANG_ENGLISH_AUS,
        EnglishCan = SUBLANG_ENGLISH_CAN,
        EnglishNz = SUBLANG_ENGLISH_NZ,
        EnglishEire = SUBLANG_ENGLISH_EIRE,
        EnglishSouthAfrica = SUBLANG_ENGLISH_SOUTH_AFRICA,
        EnglishJamaica = SUBLANG_ENGLISH_JAMAICA,
        EnglishCaribbean = SUBLANG_ENGLISH_CARIBBEAN,
        EnglishBelize = SUBLANG_ENGLISH_BELIZE,
        EnglishTrinidad = SUBLANG_ENGLISH_TRINIDAD,
        EnglishZimbabwe = SUBLANG_ENGLISH_ZIMBABWE,
        EnglishPhilippines = SUBLANG_ENGLISH_PHILIPPINES,
        EnglishIndia = SUBLANG_ENGLISH_INDIA,
        EnglishMalaysia = SUBLANG_ENGLISH_MALAYSIA,
        EnglishSingapore = SUBLANG_ENGLISH_SINGAPORE,
        EstonianEstonia = SUBLANG_ESTONIAN_ESTONIA,
        FaeroeseFaroeIslands = SUBLANG_FAEROESE_FAROE_ISLANDS,
        FilipinoPhilippines = SUBLANG_FILIPINO_PHILIPPINES,
        FinnishFinland = SUBLANG_FINNISH_FINLAND,
        French = SUBLANG_FRENCH,
        FrenchBelgian = SUBLANG_FRENCH_BELGIAN,
        FrenchCanadian = SUBLANG_FRENCH_CANADIAN,
        FrenchSwiss = SUBLANG_FRENCH_SWISS,
        FrenchLuxembourg = SUBLANG_FRENCH_LUXEMBOURG,
        FrenchMonaco = SUBLANG_FRENCH_MONACO,
        FrisianNetherlands = SUBLANG_FRISIAN_NETHERLANDS,
        FulahSenegal = SUBLANG_FULAH_SENEGAL,
        GalicianGalician = SUBLANG_GALICIAN_GALICIAN,
        GeorgianGeorgia = SUBLANG_GEORGIAN_GEORGIA,
        German = SUBLANG_GERMAN,
        GermanSwiss = SUBLANG_GERMAN_SWISS,
        GermanAustrian = SUBLANG_GERMAN_AUSTRIAN,
        GermanLuxembourg = SUBLANG_GERMAN_LUXEMBOURG,
        GermanLiechtenstein = SUBLANG_GERMAN_LIECHTENSTEIN,
        GreekGreece = SUBLANG_GREEK_GREECE,
        GreenlandicGreenland = SUBLANG_GREENLANDIC_GREENLAND,
        GujaratiIndia = SUBLANG_GUJARATI_INDIA,
        HausaNigeriaLatin = SUBLANG_HAUSA_NIGERIA_LATIN,
        HawaiianUs = SUBLANG_HAWAIIAN_US,
        HebrewIsrael = SUBLANG_HEBREW_ISRAEL,
        HindiIndia = SUBLANG_HINDI_INDIA,
        HungarianHungary = SUBLANG_HUNGARIAN_HUNGARY,
        IcelandicIceland = SUBLANG_ICELANDIC_ICELAND,
        IgboNigeria = SUBLANG_IGBO_NIGERIA,
        IndonesianIndonesia = SUBLANG_INDONESIAN_INDONESIA,
        InuktitutCanada = SUBLANG_INUKTITUT_CANADA,
        InuktitutCanadaLatin = SUBLANG_INUKTITUT_CANADA_LATIN,
        IrishIreland = SUBLANG_IRISH_IRELAND,
        Italian = SUBLANG_ITALIAN,
        ItalianSwiss = SUBLANG_ITALIAN_SWISS,
        JapaneseJapan = SUBLANG_JAPANESE_JAPAN,
        KannadaIndia = SUBLANG_KANNADA_INDIA,
        KashmiriSasia = SUBLANG_KASHMIRI_SASIA,
        KashmiriIndia = SUBLANG_KASHMIRI_INDIA,
        KazakKazakhstan = SUBLANG_KAZAK_KAZAKHSTAN,
        KhmerCambodia = SUBLANG_KHMER_CAMBODIA,
        KicheGuatemala = SUBLANG_KICHE_GUATEMALA,
        KinyarwandaRwanda = SUBLANG_KINYARWANDA_RWANDA,
        KonkaniIndia = SUBLANG_KONKANI_INDIA,
        Korean = SUBLANG_KOREAN,
        KyrgyzKyrgyzstan = SUBLANG_KYRGYZ_KYRGYZSTAN,
        LaoLao = SUBLANG_LAO_LAO,
        LatvianLatvia = SUBLANG_LATVIAN_LATVIA,
        Lithuanian = SUBLANG_LITHUANIAN,
        LowerSorbianGermany = SUBLANG_LOWER_SORBIAN_GERMANY,
        LuxembourgishLuxembourg = SUBLANG_LUXEMBOURGISH_LUXEMBOURG,
        MacedonianMacedonia = SUBLANG_MACEDONIAN_MACEDONIA,
        MalayMalaysia = SUBLANG_MALAY_MALAYSIA,
        MalayBruneiDarussalam = SUBLANG_MALAY_BRUNEI_DARUSSALAM,
        MalayalamIndia = SUBLANG_MALAYALAM_INDIA,
        MalteseMalta = SUBLANG_MALTESE_MALTA,
        MaoriNewZealand = SUBLANG_MAORI_NEW_ZEALAND,
        MapudungunChile = SUBLANG_MAPUDUNGUN_CHILE,
        MarathiIndia = SUBLANG_MARATHI_INDIA,
        MohawkMohawk = SUBLANG_MOHAWK_MOHAWK,
        MongolianCyrillicMongolia = SUBLANG_MONGOLIAN_CYRILLIC_MONGOLIA,
        MongolianPrc = SUBLANG_MONGOLIAN_PRC,
        NepaliIndia = SUBLANG_NEPALI_INDIA,
        NepaliNepal = SUBLANG_NEPALI_NEPAL,
        NorwegianBokmal = SUBLANG_NORWEGIAN_BOKMAL,
        NorwegianNynorsk = SUBLANG_NORWEGIAN_NYNORSK,
        OccitanFrance = SUBLANG_OCCITAN_FRANCE,
        OdiaIndia = SUBLANG_ODIA_INDIA,
        OriyaIndia = SUBLANG_ORIYA_INDIA,
        PashtoAfghanistan = SUBLANG_PASHTO_AFGHANISTAN,
        PersianIran = SUBLANG_PERSIAN_IRAN,
        PolishPoland = SUBLANG_POLISH_POLAND,
        Portuguese = SUBLANG_PORTUGUESE,
        PortugueseBrazilian = SUBLANG_PORTUGUESE_BRAZILIAN,
        PularSenegal = SUBLANG_PULAR_SENEGAL,
        PunjabiIndia = SUBLANG_PUNJABI_INDIA,
        PunjabiPakistan = SUBLANG_PUNJABI_PAKISTAN,
        QuechuaBolivia = SUBLANG_QUECHUA_BOLIVIA,
        QuechuaEcuador = SUBLANG_QUECHUA_ECUADOR,
        QuechuaPeru = SUBLANG_QUECHUA_PERU,
        RomanianRomania = SUBLANG_ROMANIAN_ROMANIA,
        RomanshSwitzerland = SUBLANG_ROMANSH_SWITZERLAND,
        RussianRussia = SUBLANG_RUSSIAN_RUSSIA,
        SakhaRussia = SUBLANG_SAKHA_RUSSIA,
        SamiNorthernNorway = SUBLANG_SAMI_NORTHERN_NORWAY,
        SamiNorthernSweden = SUBLANG_SAMI_NORTHERN_SWEDEN,
        SamiNorthernFinland = SUBLANG_SAMI_NORTHERN_FINLAND,
        SamiLuleNorway = SUBLANG_SAMI_LULE_NORWAY,
        SamiLuleSweden = SUBLANG_SAMI_LULE_SWEDEN,
        SamiSouthernNorway = SUBLANG_SAMI_SOUTHERN_NORWAY,
        SamiSouthernSweden = SUBLANG_SAMI_SOUTHERN_SWEDEN,
        SamiSkoltFinland = SUBLANG_SAMI_SKOLT_FINLAND,
        SamiInariFinland = SUBLANG_SAMI_INARI_FINLAND,
        SanskritIndia = SUBLANG_SANSKRIT_INDIA,
        ScottishGaelic = SUBLANG_SCOTTISH_GAELIC,
        SerbianBosniaHerzegovinaLatin =
                SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_LATIN,
        SerbianBosniaHerzegovinaCyrillic =
                SUBLANG_SERBIAN_BOSNIA_HERZEGOVINA_CYRILLIC,
        SerbianMontenegroLatin = SUBLANG_SERBIAN_MONTENEGRO_LATIN,
        SerbianMontenegroCyrillic = SUBLANG_SERBIAN_MONTENEGRO_CYRILLIC,
        SerbianSerbiaLatin = SUBLANG_SERBIAN_SERBIA_LATIN,
        SerbianSerbiaCyrillic = SUBLANG_SERBIAN_SERBIA_CYRILLIC,
        SerbianCroatia = SUBLANG_SERBIAN_CROATIA,
        SerbianLatin = SUBLANG_SERBIAN_LATIN,
        SerbianCyrillic = SUBLANG_SERBIAN_CYRILLIC,
        SindhiIndia = SUBLANG_SINDHI_INDIA,
        SindhiPakistan = SUBLANG_SINDHI_PAKISTAN,
        SindhiAfghanistan = SUBLANG_SINDHI_AFGHANISTAN,
        SinhaleseSriLanka = SUBLANG_SINHALESE_SRI_LANKA,
        SothoNorthernSouthAfrica = SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA,
        SlovakSlovakia = SUBLANG_SLOVAK_SLOVAKIA,
        SlovenianSlovenia = SUBLANG_SLOVENIAN_SLOVENIA,
        Spanish = SUBLANG_SPANISH,
        SpanishMexican = SUBLANG_SPANISH_MEXICAN,
        SpanishModern = SUBLANG_SPANISH_MODERN,
        SpanishGuatemala = SUBLANG_SPANISH_GUATEMALA,
        SpanishCostaRica = SUBLANG_SPANISH_COSTA_RICA,
        SpanishPanama = SUBLANG_SPANISH_PANAMA,
        SpanishDominicanRepublic = SUBLANG_SPANISH_DOMINICAN_REPUBLIC,
        SpanishVenezuela = SUBLANG_SPANISH_VENEZUELA,
        SpanishColombia = SUBLANG_SPANISH_COLOMBIA,
        SpanishPeru = SUBLANG_SPANISH_PERU,
        SpanishArgentina = SUBLANG_SPANISH_ARGENTINA,
        SpanishEcuador = SUBLANG_SPANISH_ECUADOR,
        SpanishChile = SUBLANG_SPANISH_CHILE,
        SpanishUruguay = SUBLANG_SPANISH_URUGUAY,
        SpanishParaguay = SUBLANG_SPANISH_PARAGUAY,
        SpanishBolivia = SUBLANG_SPANISH_BOLIVIA,
        SpanishElSalvador = SUBLANG_SPANISH_EL_SALVADOR,
        SpanishHonduras = SUBLANG_SPANISH_HONDURAS,
        SpanishNicaragua = SUBLANG_SPANISH_NICARAGUA,
        SpanishPuertoRico = SUBLANG_SPANISH_PUERTO_RICO,
        SpanishUs = SUBLANG_SPANISH_US,
        SwahiliKenya = SUBLANG_SWAHILI_KENYA,
        Swedish = SUBLANG_SWEDISH,
        SwedishFinland = SUBLANG_SWEDISH_FINLAND,
        SyriacSyria = SUBLANG_SYRIAC_SYRIA,
        TajikTajikistan = SUBLANG_TAJIK_TAJIKISTAN,
        TamazightAlgeriaLatin = SUBLANG_TAMAZIGHT_ALGERIA_LATIN,
        TamazightMoroccoTifinagh = SUBLANG_TAMAZIGHT_MOROCCO_TIFINAGH,
        TamilIndia = SUBLANG_TAMIL_INDIA,
        TamilSriLanka = SUBLANG_TAMIL_SRI_LANKA,
        TatarRussia = SUBLANG_TATAR_RUSSIA,
        TeluguIndia = SUBLANG_TELUGU_INDIA,
        ThaiThailand = SUBLANG_THAI_THAILAND,
        TibetanPrc = SUBLANG_TIBETAN_PRC,
        TigrignaEritrea = SUBLANG_TIGRIGNA_ERITREA,
        TigrinyaEritrea = SUBLANG_TIGRINYA_ERITREA,
        TigrinyaEthiopia = SUBLANG_TIGRINYA_ETHIOPIA,
        TswanaBotswana = SUBLANG_TSWANA_BOTSWANA,
        TswanaSouthAfrica = SUBLANG_TSWANA_SOUTH_AFRICA,
        TurkishTurkey = SUBLANG_TURKISH_TURKEY,
        TurkmenTurkmenistan = SUBLANG_TURKMEN_TURKMENISTAN,
        UighurPrc = SUBLANG_UIGHUR_PRC,
        UkrainianUkraine = SUBLANG_UKRAINIAN_UKRAINE,
        UpperSorbianGermany = SUBLANG_UPPER_SORBIAN_GERMANY,
        UrduPakistan = SUBLANG_URDU_PAKISTAN,
        UrduIndia = SUBLANG_URDU_INDIA,
        UzbekLatin = SUBLANG_UZBEK_LATIN,
        UzbekCyrillic = SUBLANG_UZBEK_CYRILLIC,
        ValencianValencia = SUBLANG_VALENCIAN_VALENCIA,
        VietnameseVietnam = SUBLANG_VIETNAMESE_VIETNAM,
        WelshUnitedKingdom = SUBLANG_WELSH_UNITED_KINGDOM,
        WolofSenegal = SUBLANG_WOLOF_SENEGAL,
        XhosaSouthAfrica = SUBLANG_XHOSA_SOUTH_AFRICA,
        YakutRussia = SUBLANG_YAKUT_RUSSIA,
        YiPrc = SUBLANG_YI_PRC,
        YorubaNigeria = SUBLANG_YORUBA_NIGERIA,
        ZuluSouthAfrica = SUBLANG_ZULU_SOUTH_AFRICA
    };
#endif
#ifndef TEXTFORMAT
#define TEXTFORMAT

    enum class TextFormat : uint32_t {
        top = DT_TOP,
        left = DT_LEFT,
        center = DT_CENTER,
        right = DT_RIGHT,
        vCenter = DT_VCENTER,
        bottom = DT_BOTTOM,
        wordBreak = DT_WORDBREAK,
        singleLine = DT_SINGLELINE,
        expandTabs = DT_EXPANDTABS,
        tabStop = DT_TABSTOP,
        noClip = DT_NOCLIP,
        externalLeading = DT_EXTERNALLEADING,
        calcRect = DT_CALCRECT,
        noPrefix = DT_NOPREFIX,
        internal = DT_INTERNAL,
        editControl = DT_EDITCONTROL,
        pathEllipsis = DT_PATH_ELLIPSIS,
        endEllipsis = DT_END_ELLIPSIS,
        modifyString = DT_MODIFYSTRING,
        rtlReading = DT_RTLREADING,
        wordEllipsis = DT_WORD_ELLIPSIS,
        noFullwidthCharBreak = DT_NOFULLWIDTHCHARBREAK,
        hidePrefix = DT_HIDEPREFIX,
        prefixOnly = DT_PREFIXONLY,
    };

    inline TextFormat operator|(TextFormat a, TextFormat b) {
        return static_cast<TextFormat>(static_cast<uint32_t>(a) |
                                       static_cast<uint32_t>(b));
    }
#endif
#ifndef OUTPUTOPTION
#define OUTPUTOPTION

    enum class OutputOption : uint32_t {
        Opaque = ETO_OPAQUE,
        Clipped = ETO_CLIPPED,
        GlyphIndex = ETO_GLYPH_INDEX,
        RtlReading = ETO_RTLREADING,
        NumericsLocal = ETO_NUMERICSLOCAL,
        NumericsLatin = ETO_NUMERICSLATIN,
        IgnoreLanguage = ETO_IGNORELANGUAGE,
        PDY = ETO_PDY,
        ReverseIndexMap = ETO_REVERSE_INDEX_MAP,
    };

    inline OutputOption operator|(OutputOption a, OutputOption b) {
        return static_cast<OutputOption>(static_cast<uint32_t>(a) |
                                         static_cast<uint32_t>(b));
    }
#endif
#ifndef DPASEARCHOPTION
#define DPASEARCHOPTION
    enum class DPASearchOption : uint32_t {
        Sorted = DPAS_SORTED,
        InsertBefore = DPAS_INSERTBEFORE,
        InsertAfter = DPAS_INSERTAFTER,
    };
    inline DPASearchOption operator|(DPASearchOption a, DPASearchOption b) {
        return static_cast<DPASearchOption>(static_cast<uint32_t>(a) |
                                            static_cast<uint32_t>(b));
    }
#endif
#ifndef DPAMERGEOPTION
#define DPAMERGEOPTION
    enum class DPAMergeOption : uint32_t {
        Sorted = DPAM_SORTED,
        Normal = DPAM_NORMAL,
        Union = DPAM_UNION,
        Intersect = DPAM_INTERSECT,
    };
    inline DPAMergeOption operator|(DPAMergeOption a, DPAMergeOption b) {
        return static_cast<DPAMergeOption>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
#ifndef READERMODEFLAG
#define READERMODEFLAG
    enum class ReaderModeFlag : uint32_t {
        ZeroCursor = 1,
        VerticalOnly = 2,
        HorizontalOnly = 4,
    };
    inline ReaderModeFlag operator|(ReaderModeFlag a, ReaderModeFlag b) {
        return static_cast<ReaderModeFlag>(static_cast<uint32_t>(a) |
                                           static_cast<uint32_t>(b));
    }
#endif
    struct ReaderModeInfo;
    typedef int32_t(CALLBACK *ReaderScroll)(_In_ ReaderModeInfo *info,
                                            _In_ int32_t horiz,
                                            _In_ int32_t vert);
    typedef int32_t(CALLBACK *TranslateDispatch)(_In_ const MSG *msg);
    struct ReaderModeInfo {
        uint32_t size;
        HWND window_handle;
        uint32_t flag;
        RECT *rect;
        ReaderScroll scroll_callback;
        TranslateDispatch dispatch_callback;
        LPARAM lparam;
    };
#ifndef NOTIFYFORMATRET
#define NOTIFYFORMATRET
    enum class NotifyFormatRet : int64_t {
        Error = 0,
        ANSI = NFR_ANSI,
        Unicode = NFR_UNICODE,
    };
#endif
#ifndef GENERALMESSAGE
#define GENERALMESSAGE
    enum class GeneralMessage : uint32_t {
        DpiScale = CCM_DPISCALE,
        GetUnicodeFormat = CCM_GETUNICODEFORMAT,
        GetVersion = CCM_GETVERSION,
        SetUnicodeFormat = CCM_SETUNICODEFORMAT,
        SetVersion = CCM_SETVERSION,
        SetWindowTheme = CCM_SETWINDOWTHEME,
        Notify = WM_NOTIFY,
        NotifyFormat = WM_NOTIFYFORMAT,
    };
#endif
#ifndef GENERALNOTIFY
#define GENERALNOTIFY
    enum class GeneralNotify : uint32_t {
        Char = NM_CHAR,
        CustomText = NM_CUSTOMTEXT,
        FontChanged = NM_FONTCHANGED,
        GetCustomSplitRect = NM_GETCUSTOMSPLITRECT,
        Hover = NM_HOVER,
        KeyDown = NM_KEYDOWN,
        KillFocus = NM_KILLFOCUS,
        LeftDown = NM_LDOWN,
        NcHitTest = NM_NCHITTEST,
        OutOfMemory = NM_OUTOFMEMORY,
        RightDown = NM_RDOWN,
        ReleasedCapture = NM_RELEASEDCAPTURE,
        Return = NM_RETURN,
        SetCursor = NM_SETCURSOR,
        SetFocus = NM_SETFOCUS,
        ThemeChanged = NM_THEMECHANGED,
        ToolTipsCreated = NM_TOOLTIPSCREATED,
        TVStateImageChanging = NM_TVSTATEIMAGECHANGING,
    };
#endif
    class general {
    private:
        uint32_t error_code = 0;

    public:
        general(const general &other) = delete;

        general(general &&other) = delete;

        general &operator=(const general &other) = delete;

        general &operator=(general &&other) = delete;

        general() = default;

        ~general() = default;

        bool init_common_controls(const INITCOMMONCONTROLSEX *icc);

        INITCOMMONCONTROLSEX
        make_icc(InitCommControlsFlag flag = InitCommControlsFlag::ListView |
                         InitCommControlsFlag::TreeView |
                         InitCommControlsFlag::Bar | InitCommControlsFlag::Tab |
                         InitCommControlsFlag::UpDown |
                         InitCommControlsFlag::Progress |
                         InitCommControlsFlag::HotKey |
                         InitCommControlsFlag::Animate |
                         InitCommControlsFlag::Win95 |
                         InitCommControlsFlag::Date |
                         InitCommControlsFlag::UserEx |
                         InitCommControlsFlag::Cool |
                         InitCommControlsFlag::Internet |
                         InitCommControlsFlag::PageScroller |
                         InitCommControlsFlag::NativeFntCtl |
                         InitCommControlsFlag::Standard |
                         InitCommControlsFlag::Link);

        LANGID
        make_lang_id(GeneralLangID lang = GeneralLangID::ChineseSimplified,
                     GeneralSubLangId sub_lang =
                             GeneralSubLangId::ChineseSimplified);

        void init_mui_lang(LANGID lang_id);

        LANGID get_mui_lang();

        std::pair<GeneralLangID, GeneralSubLangId> get_mui_lang2();

        bool
        load_icon_metric(HINSTANCE instance_handle,
                         std::string &name,
                         HICON *icon_handle,
                         bool is_small = false,
                         helper::CodePage code_page = helper::curr_code_page());

        bool load_icon_metric(HINSTANCE instance_handle,
                              std::wstring &name,
                              HICON *icon_handle,
                              bool is_small = false);

        bool load_icon_with_scale_down(
                HINSTANCE instance_handle,
                std::string &name,
                int32_t width,
                int32_t height,
                HICON *icon_handle,
                helper::CodePage code_page = helper::curr_code_page());

        bool load_icon_with_scale_down(HINSTANCE instance_handle,
                                       std::wstring &name,
                                       int32_t width,
                                       int32_t height,
                                       HICON *icon_handle);

        bool mirror_icon(HICON *icon_handle_small, HICON *icon_handle_large);

        int32_t
        draw_shadow_text(HDC dc_handle,
                         std::string &text,
                         RECT *rect,
                         TextFormat format,
                         COLORREF text_color,
                         COLORREF shadow_color,
                         int32_t offset_x,
                         int32_t offset_y,
                         helper::CodePage code_page = helper::curr_code_page());

        int32_t draw_shadow_text(HDC dc_handle,
                                 std::wstring &text,
                                 RECT *rect,
                                 TextFormat format,
                                 COLORREF text_color,
                                 COLORREF shadow_color,
                                 int32_t offset_x,
                                 int32_t offset_y);

        int32_t
        draw_text_wrap(HDC dc_handle,
                       std::string &text,
                       RECT *rect,
                       TextFormat format,
                       DRAWTEXTPARAMS *param = nullptr,
                       helper::CodePage code_page = helper::curr_code_page());

        int32_t draw_text_wrap(HDC dc_handle,
                               std::wstring &text,
                               RECT *rect,
                               TextFormat format,
                               DRAWTEXTPARAMS *param = nullptr);

        int32_t draw_text_priv_wrap(
                HDC dc_handle,
                std::string &text,
                RECT *rect,
                TextFormat format,
                DRAWTEXTPARAMS *param = nullptr,
                helper::CodePage code_page = helper::curr_code_page());

        int32_t draw_text_priv_wrap(HDC dc_handle,
                                    std::wstring &text,
                                    RECT *rect,
                                    TextFormat format,
                                    DRAWTEXTPARAMS *param = nullptr);

        bool
        text_out_wrap(HDC dc_handle,
                      int32_t x,
                      int32_t y,
                      OutputOption option,
                      const RECT *rect,
                      std::string &text,
                      const int32_t dx[],
                      helper::CodePage code_page = helper::curr_code_page());

        bool text_out_wrap(HDC dc_handle,
                           int32_t x,
                           int32_t y,
                           OutputOption option,
                           const RECT *rect,
                           std::wstring &text,
                           const int32_t dx[]);

        bool get_text_extent_point32_wrap(
                HDC dc_handle,
                std::string &text,
                SIZE *size,
                helper::CodePage code_page = helper::curr_code_page());

        bool get_text_extent_point32_wrap(HDC dc_handle,
                                          std::wstring &text,
                                          SIZE *size);

        ReaderModeInfo
        make_reader_mode_info(HWND window_handle,
                              ReaderModeFlag flag,
                              RECT *rect,
                              ReaderScroll scroll_callback,
                              LPARAM lparam,
                              TranslateDispatch dispatch_callback);

        void do_reader_mode(ReaderModeInfo *reader_mode_info);

        void get_effective_client_rect(HWND window_handle,
                                       RECT *rect,
                                       const int32_t info[]);

        bool show_hide_menu_control(HWND window_handle,
                                    uintptr_t menu_item_id,
                                    int32_t info[]);

        // forward notify to SendMessageW
        LRESULT
        forward_notify(HWND window_handle, int32_t send_item_id, NMHDR *hdr);

        // forward notify to PostMessageW
        bool
        forward_notify2(HWND window_handle, int32_t send_item_id, NMHDR *hdr);

        typedef void(CALLBACK *HandleNotify)(HWND, int32_t, NMHDR *);

        void handle_notify(HWND window_handle,
                           WPARAM wparam,
                           LPARAM lparam,
                           HandleNotify fn);

        uint32_t index_to_state_image_mask(int32_t index);

        void dpi_scale(HWND window_handle);

        void
        set_window_theme(HWND window_handle,
                         std::string &theme,
                         helper::CodePage code_page = helper::curr_code_page());

        void set_window_theme(HWND window_handle, std::wstring &theme);

        void notify(HWND parent_window_handle, int64_t control_id, NMHDR *hdr);

        NotifyFormatRet notify_format(HWND parent_window_handle,
                                      HWND control_handle);

        NotifyFormatRet notify_format2(HWND control_handle,
                                       HWND parent_window_handle);

        int64_t get_version(HWND window_handle);

        int64_t set_version(HWND window_handle, int64_t version);

        bool is_ansi_format(HWND window_handle);

        bool is_unicode_format(HWND window_handle);

        void set_ansi_format(HWND window_handle);

        void set_unicode_format(HWND window_handle);

        [[nodiscard]] uint32_t err_code() const;

        [[nodiscard]] std::string err_string() const;

        [[nodiscard]] std::wstring err_wstring() const;
    };

    class dpa {
    public:
        dpa(const dpa &other) = delete;

        dpa(dpa &&other) = delete;

        dpa &operator=(const dpa &other) = delete;

        dpa &operator=(dpa &&other) = delete;

        dpa() = default;

        ~dpa() = default;

        static HDPA create(int32_t grow);

        static HDPA create(int32_t grow, HANDLE heap_handle);

        static HDPA clone(HDPA dpa_handle, HDPA new_dpa_handle);

        static int32_t insert_ptr(HDPA dpa_handle, int32_t index, void *ptr);

        static int32_t append_ptr(HDPA dpa_handle, void *ptr);

        static void *get_ptr(HDPA dpa_handle, int32_t index);

        static bool set_ptr(HDPA dpa_handle, int32_t index, void *ptr);

        static void **get_ptr_ptr(HDPA dpa_handle);

        static void *fast_get_ptr(HDPA dpa_handle, int32_t index);

        static void fast_delete_last_ptr(HDPA dpa_handle);

        static void *delete_ptr(HDPA dpa_handle, int32_t index);

        static bool delete_all_ptrs(HDPA dpa_handle);

        static bool destroy(HDPA dpa_handle);

        static int32_t get_ptr_count(HDPA dpa_handle);

        static int32_t set_ptr_count(HDPA dpa_handle, int32_t count);

        static int32_t get_ptr_index(HDPA dpa_handle, void *ptr);

        static uint64_t get_size(HDPA dpa_handle);

        static bool grow(HDPA dpa_handle, int32_t ptr_num);

        static int32_t search(HDPA dpa_handle,
                              void *search,
                              int32_t start,
                              PFNDACOMPARE compare,
                              LPARAM lparam,
                              DPASearchOption option);

        static bool sort(HDPA dpa_handle, PFNDACOMPARE compare, LPARAM lparam);

        static int32_t sorted_insert_ptr(HDPA dpa_handle,
                                         void *search,
                                         int32_t start,
                                         PFNDACOMPARE compare,
                                         LPARAM lparam,
                                         DPASearchOption option,
                                         void *ptr);

        static bool merge(HDPA dpa_handle_dst,
                          HDPA dpa_handle_src,
                          DPAMergeOption option,
                          PFNDACOMPARE compare,
                          PFNDPAMERGE merge,
                          LPARAM lparam);

        static void
        enum_callback(HDPA dpa_handle, PFNDAENUMCALLBACK callback, void *data);

        static void destroy_callback(HDPA dpa_handle,
                                     PFNDAENUMCALLBACK callback,
                                     void *data);

        static bool load_stream(HDPA *dpa_handle,
                                IStream *stream,
                                PFNDPASTREAM callback,
                                void *data);

        static bool save_stream(HDPA dpa_handle,
                                IStream *stream,
                                PFNDPASTREAM callback,
                                void *data);
    };

    class dsa {
    public:
        dsa(const dsa &other) = delete;

        dsa(dsa &&other) = delete;

        dsa &operator=(const dsa &other) = delete;

        dsa &operator=(dsa &&other) = delete;

        dsa() = default;

        ~dsa() = default;

        static HDSA create(int32_t item_size, int32_t item_count);

        static HDSA clone(HDSA dsa_handle);

        static int32_t insert_item(HDSA dsa_handle, int32_t index, void *item);

        static int32_t append_item(HDSA dsa_handle, void *item);

        static bool get_item(HDSA dsa_handle, int32_t index, void *item);

        static bool set_item(HDSA dsa_handle, int32_t index, void *item);

        static int32_t get_item_count(HDSA dsa_handle);

        static void *get_item_ptr(HDSA dsa_handle, int32_t index);

        static uint64_t get_size(HDSA dsa_handle);

        static bool sort(HDSA dsa_handle, PFNDACOMPARE compare, LPARAM lparam);

        static bool delete_item(HDSA dsa_handle, int32_t index);

        static bool delete_all_items(HDSA dsa_handle);

        static bool destroy(HDSA dsa_handle);

        static void
        enum_callback(HDSA dsa_handle, PFNDAENUMCALLBACK callback, void *data);

        static void destroy_callback(HDSA dsa_handle,
                                     PFNDAENUMCALLBACK callback,
                                     void *data);
    };
} // namespace YanLib::ui::components
#endif // GENERAL_H
