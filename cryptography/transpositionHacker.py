import detectEnglish, transposition_cipher_decryption

def hackTransposition(message):
    print('Hacking...')

    print('(Press Ctrl-C or Ctrl-D to quit at any time.)')

    for key in range(1, len(message)):
        print('Trying key #%s...' % (key))

        decryptedText = transposition_cipher_decryption.decrypt_transposition_cipher(key, message)

        if detectEnglish.isEnglish(decryptedText):
            print()
            print('Possible encryption hack: ')
            print('Key %s: %s' %(key, decryptedText[:100]))
            print()
            print('Enter D for done, or just press Enter to continue hacking: ')
            response = input('> ')
            if response.strip().upper().startswith('D'):
                return decryptedText

    return None


if __name__ == '__main__':
    # myMessage = """Cb b rssti aieih rooaopbrtnsceee er es no npfgcwu  plri ch nitaalr eiuengiteehb(e1  hilincegeoamn fubehgtarndcstudmd nM eu eacBoltaeteeoinebcdkyremdteghn.aa2r81a condari fmps" tad   l t oisn sit u1rnd stara nvhn fsedbh ee,n  e necrg6  8nmisv l nc muiftegiitm tutmg cm shSs9fcie ebintcaets h  aihda cctrhe ele 1O7 aaoem waoaatdahretnhechaopnooeapece9etfncdbgsoeb uuteitgna.rteoh add e,D7c1Etnpneehtn beete" evecoal lsfmcrl iu1cifgo ai. sl1rchdnheev sh meBd ies e9t)nh,htcnoecplrrh ,ide hmtlme. pheaLem,toeinfgn t e9yce da' eN eMp a ffn Fc1o ge eohg dere.eec s nfap yox hla yon. lnrnsreaBoa t,e eitsw il ulpbdofgBRe bwlmprraio po  droB wtinue r Pieno nc ayieeto'lulcih sfnc  ownaSserbereiaSm-eaiah, nnrttgcC  maciiritvledastinideI  nn rms iehn tsigaBmuoetcetias rn|"""
    myMessage = "Tsih dtlhdao tqh rhttmyd  ei e,roti g g.g  htgae eio ,utmie  inh neIi  e,cum.ueaeeiheieew em  ,rhtbmhi  tue akyt.nrh lhengpon.esg tftf  hlo irnd oenncxhhdoph eo eeenNson sneeh  nesden irfgro t forgbadvSn d dn tgiaaa.reot um nraoe tmh  seTterh  tano  emirwi orue ehte ii m, pctd eewhsgiat ttemioeth  hhr esm n csa eneactmotlsmeeypnroo tht  T reehhg  iihmolm oeotee e eoadtetgwt esue u  ee dee efvtoelsshsev ethfomoiev eb rfrn oywevg hsaaaht. lltnRcens setc er ryhpehdem  tifanndetnet fe cfeo eabesri|"
    hackedMessage = hackTransposition(myMessage)

    if hackedMessage == None:
        print('Failed to hack encryption.')
    else:
        print('Copying hacked message to clipboard:')
        print(hackedMessage)

