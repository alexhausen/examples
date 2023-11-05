package main

import (
	"errors"
	"fmt"
	"net/http"
	"strings"
	"time"
	"webapp/pkg/data"

	"github.com/golang-jwt/jwt/v4"
)

var jwtTokenExpiry = time.Minute * 15
var refreshTokenExpiry = time.Hour * 24

type TokenPair struct {
	Token        string `json:"access_token"`
	RefreshToken string `json:"refresh_token"`
}

type Claims struct {
	UserName string `json:"name"`
	jwt.RegisteredClaims
}

func (app *application) getTokenFromHeaderAndVerify(w http.ResponseWriter, r *http.Request) (string, *Claims, error) {
	// add a header
	w.Header().Add("Vary", "Authorization")
	//get the authorization header
	authHeader := r.Header.Get("Authorization")
	//sanity check
	if authHeader == "" {
		return "", nil, errors.New("no auth header")
	}
	// split the header on spaces
	headerParts := strings.Split(authHeader, " ")
	if len(headerParts) != 2 {
		return "", nil, errors.New("invalid auth header")
	}
	// check Bearer
	if headerParts[0] != "Bearer" {
		return "", nil, errors.New("unauthorized: no Bearer")
	}
	token := headerParts[1]
	// declare an empty Claims
	claims := &Claims{}
	// parse token with our claims using secret
	_, err := jwt.ParseWithClaims(token, claims, func(token *jwt.Token) (interface{}, error) {
		//validate the signing method algorithm
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
		}
		return []byte(app.JWTSecret), nil
	})
	// check error; note: also expired tokens
	if err != nil {
		if strings.HasPrefix(err.Error(), "token is expired by") {
			return "", nil, errors.New("expired token")
		}
		return "", nil, err
	}
	// make sure that we issued this token
	if claims.Issuer != app.Domain {
		return "", nil, errors.New("incorrect issuer")
	}
	// valid token
	return token, claims, nil
}

func (app *application) generateTokenPair(user *data.User) (TokenPair, error) {
	// create a JWT token
	token := jwt.New(jwt.SigningMethodHS256)
	// set claims
	claims := token.Claims.(jwt.MapClaims)
	claims["name"] = fmt.Sprintf("%s %s", user.FirstName, user.LastName)
	claims["sub"] = fmt.Sprint(user.ID) // subject
	claims["aud"] = app.Domain          // audience
	claims["iss"] = app.Domain          // issuer
	claims["admin"] = user.IsAdmin == 1
	claims["exp"] = time.Now().Add(jwtTokenExpiry).Unix() // expiry
	// sign the token
	signedAccessToken, err := token.SignedString([]byte(app.JWTSecret))
	if err != nil {
		return TokenPair{}, err
	}
	// create the refresh token
	refreshToken := jwt.New(jwt.SigningMethodHS256)
	refreshTokenClaims := refreshToken.Claims.(jwt.MapClaims)
	refreshTokenClaims["sub"] = fmt.Sprint(user.ID)
	refreshTokenClaims["exp"] = time.Now().Add(refreshTokenExpiry).Unix()
	// sign the refresh token
	signedRefreshToken, err := refreshToken.SignedString([]byte(app.JWTSecret))
	if err != nil {
		return TokenPair{}, err
	}
	var tokenPair = TokenPair{
		Token:        signedAccessToken,
		RefreshToken: signedRefreshToken,
	}
	return tokenPair, nil
}
