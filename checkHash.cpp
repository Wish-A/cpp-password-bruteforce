#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <openssl/evp.h>

const std::string DIGEST_TYPE = "MD5";
EVP_MD_CTX *mdctx;
const EVP_MD *md;
unsigned char md_value[EVP_MAX_MD_SIZE];

/**
* Help routine for an efficient implementation of the MD5 hash routine
 */
void initMD5(){
	md = EVP_get_digestbyname( DIGEST_TYPE.c_str() );
}

/**
 * Stretch the MD5 hash of a string and returns the result in hex notation
 * @param  bron         String to be hashed
 * * @return            The MD5 has in HEX
 */
std::string calcMD5( std::string bron ) {

	unsigned int md_len;

	mdctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, bron.c_str(), bron.length() );
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_destroy(mdctx);

	// We now have the hash in Bytes
	// We will convert this to HEX string
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for (size_t i = 0; i < (size_t) md_len; i++) {
		ss << std::setw(2) << (int) md_value[i];
	}
	return ss.str();
}

/**
 * Help routine for an efficient implementation of the MD5 hash routine.
 */
void exitMD5(){
	EVP_cleanup();
}

/**
 * 						Read in hashes.
 *              		These are the hashes of which we want to determine the source (= password).
 *              		We read it from a text file. 1 hash per line.
 * @param filenm        The hash-file's filename
 *                                      
 * @return              a vector<string> with the hashes
 */
std::vector<std::string> readhashes( std::string filenm ){
	std::vector<std::string> hashes;
	std::ifstream hashfile( filenm );
	if ( !hashfile.is_open() ) {
		std::cout << "File kan niet worden geopend: " + filenm << std::endl;
		std::cout << "exit !"<< std::endl;
		exit(EXIT_FAILURE);
	}
	for( std::string regel; getline( hashfile, regel); ) {
		hashes.push_back(regel);
	}
	return hashes;
}

/**
 * main
 * 						The program reads a number of hashes from a file. 
 * 						Then per lines offered via stdin * an MD5 hash determined. This is compared with the read-in hashes. 
 * 						In a match, a line is written to output.
 * @param  argc         Has to be equal to 1
 * @param  argv         Has to include name of the hashes
 * @return              Exit_FAILURE if an error occurs, otherwise 0;
 */
int main(int argc, char const *argv[]) {
	// Read all hashes from file
	if (argc != 2) {
		std::cout << "geef 1 argument op : hash-file"<< std::endl;
		std::cout << "exit !"<< std::endl;
		exit(EXIT_FAILURE);
	}

	// Read all hashes in a vector, argv-1 gives the file name for the hashes.
	std::vector<std::string> hashes = readhashes( std::string( argv[1] ) );

	// Initialise MD5
	initMD5();

	// Read stdin line by line and determine the md5 hash. compare these with hashes in list
	std::string regel;
	std::string hash;
	while( getline(std::cin, regel) ) {
		hash = calcMD5(regel);
		if ( std::find(hashes.begin(), hashes.end(), hash) != hashes.end() ) {
			// SUCCES !! geef hash met wachtwoord in stdout.
			std::cout << "hash: " << hash << " - " << regel << std::endl;
		}
	}
	// MD5 abort
	exitMD5();

	return 0;
}
